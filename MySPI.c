#include "MySPI.h"
#include "io_handler.h"
#include "stm32f407xx.h"
#include "MyBitMacros.h"
#include <stdint.h>

#define SPI1_CLK_EN()	(RCC->APB2ENR |= RCC_APB2ENR_SPI1EN)
#define MY_MAX(a, b)    ((a) > (b) ? (a) : (b))

/*
* @brief Initialises SPI driver
* @details Currently only inits SPI1, and utilises DMA
* @params None
* @return void
*/
// TODO: make function configurable
void spi_open(void)
{	
	// For now, pins:
		// PA5 = SPI1_SCK
		// PA7 = SPI1_MOSI
		// PA6 = SPI1_MISO
		// PE3 = CS_I2C/SPI
	
		// PE1 = mems_int2
		// PE0 = MEMS_INT1

	// Enable clock for SPI peripheral
	SPI1_CLK_EN();
	// Enable clock for the GPIOs
	rcc_enable_gpio_port_clock(GPIO_PORT_A);
	rcc_enable_gpio_port_clock(GPIO_PORT_E);
	// Select GPIO as alternate functions
	GPIO_type spiPin = 
	{
		.port = GPIO_PORT_A,
		.pin = GPIO_PIN_5,
		.mode = GPIO_MODE_AF,
		.AFValue = AF5,
	};
	gpio_init(spiPin);	// initialise PA5 (SCK)
	spiPin.pin = GPIO_PIN_6;
	gpio_init(spiPin); // initialise PA6 (MISO)
	spiPin.pin = GPIO_PIN_7;
	gpio_init(spiPin); // init PA7 (MOSI)
	spiPin.port = GPIO_PORT_E;
	spiPin.pin = GPIO_PIN_3;
	spiPin.mode = GPIO_MODE_OUTPUT;
	gpio_init(spiPin);	// init PE3 as output (CS)
	gpio_enable(GPIO_STATE_HIGH, GPIO_PORT_E, GPIO_PIN_3); // set CS HIGH to begin with
	
	// Note: some SPI1 and SPI3 are mapped to use JTAG
	
	// 1. Select BR[2:0] bits to define serial clock baud rate in SPI_CR1 []
		// Baud rate is just the master speed. fpclk/2 max.
	MODIFY_REG(SPI1->CR1, SPI_CR1_BR_Msk, (SPI_CR1_BR_0));  // 16 / 4 MHz?
	
	// 2. Select CPOL and CPHA bits (not necessary if TI mode is selected)
	MODIFY_REG(SPI1->CR1, SPI_CR1_CPOL_Msk, SPI_CR1_CPOL);  // CPOL=1, clock high when idle
	MODIFY_REG(SPI1->CR1, SPI_CR1_CPHA_Msk, SPI_CR1_CPHA);  // CPHA = 1, second transition is first data capture edge
	
	// 3. Select DFF bit for 8 or 16  bit data frame format []
	MY_CLEAR_BIT(SPI1->CR1, SPI_CR1_DFF_Pos);  // 8 bit frame format
	 
	// 4. Configure frame format for LSB / MSB first in SPI_CR1
	MY_CLEAR_BIT(SPI1->CR1, SPI_CR1_LSBFIRST_Pos); // 0 = MSB first
	
	// 5. Configure NSS pin
	// It seems CS is connected to PE3 which is not part of the SPI1 periph. So do it ourselves...
	// NSS output enable if we want to use master mode. I expect this to do nothing to the I/Os as GPIO AF is not set
	SPI1->CR2 |= SPI_CR2_SSOE;	// enable output
	
	// 6. Set FRF bit in SPI_CR2 to select TI protocol for serial comms if needed
	// Let's use SPI Motorola mode for now as we seem to have more control over polarity
	
	// 7. Select MSTR and SPE bits. They will remain set only if NSS pin is connected to a high level signal. MOSI  is out MISO in.
	SPI1->CR1 |= SPI_CR1_MSTR;  // SPI as master mode
    
    // 8. Handle DMA
    #if (1)
    SPI1->CR2 |= SPI_CR2_RXDMAEN;   // enable receive DMA
    #endif
    
	SPI1->CR1 |= SPI_CR1_SPE; // enable SPI!
}

// Resets GPIOs and SPI1 peripheral.
void spi_close(void)
{
	MY_CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE_Pos);	// disable SPI
	SPI1->CR1 = 0;
	SPI1->CR2 = 0;
	
	// un-enable GPIO pins...
	gpio_close(GPIO_PORT_A, GPIO_PIN_5);
	gpio_close(GPIO_PORT_A, GPIO_PIN_6);
	gpio_close(GPIO_PORT_A, GPIO_PIN_7);
	gpio_close(GPIO_PORT_E, GPIO_PIN_3);
}

/* 
 * @brief Transmit and receive from SPI
 * @details Will try to read or transmit only the number of times desired.
 *          This is to keep it functionign with DMA.
 *          If DMA receive, make the read buffer 0, and the write buffer number of bytes to read
 *          If DMA transmit, make write buffer 0, and the read buffer number of bytes to write
*           TODO, check if above works. Seems awkward!
 *
*/
void spi_read_write(SpiTransfer_s* transfer)
{
    uint32_t bytesToXferReceive = MY_MAX(transfer->bytesToReceive, transfer->bytesToTransmit);
	gpio_enable(GPIO_STATE_LOW, GPIO_PORT_E, GPIO_PIN_3); // set CS low to select peripheral
	for (uint32_t i = 0; i < bytesToXferReceive; i++)
	{
        if (transfer->bytesToTransmit > 0)  // do transaction if we have bytes to transfer
        {
            while ((SPI1->SR & SPI_SR_TXE) == 0);  //TXE is 1 when it can receive another byte
            SPI1->DR = (transfer->txBuf[i]);	// off it goes!	
            transfer->bytesToTransmit--;
        }
		if (transfer->bytesToReceive > 0)   // receive
        {
            while ((SPI1->SR & SPI_SR_RXNE) == 0);	// RXNE is 1 when we have a byte to read
            (transfer->rxBuf)[i] = SPI1->DR;	// read byte
            transfer->bytesToReceive--;
        }
	}
	while ((SPI1->SR & SPI_SR_BSY) == 1);  // wait until not busy
	gpio_enable(GPIO_STATE_HIGH, GPIO_PORT_E, GPIO_PIN_3); // set CS high again to de-select peripheral
}

/*
 * @brief Returns rx buffer address as 32 bit value
 * @details Using it to hide STM32 header file
 * @params None
 * @return uint32 The address of the SPI1 data register
*/
uint32_t getSPI1RxReg(void)
{
    return (uint32_t)(&SPI1->DR); // WARNING: Assumes 32 bit addr
}
	
void spi_ioctl(void)
{}
