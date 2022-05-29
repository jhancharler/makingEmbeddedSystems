#include "MySPI.h"
#include "io_handler.h"
#include "stm32f407xx.h"
#include "MyBitMacros.h"

#define SPI1_CLK_EN()	(RCC->APB2ENR |= RCC_APB2ENR_SPI1EN)

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
	MODIFY_REG(SPI1->CR1, SPI_CR1_DFF_Msk, ~SPI_CR1_DFF); // 8bit frame format
	
	// 4. Configure frame format for LSB / MSB first in SPI_CR1
	SPI1->CR1 &= ~(SPI_CR1_LSBFIRST);  // 0 = MSB first
	
	// 5. Configure NSS pin
	// It seems CS is connected to PE3 which is not part of the SPI1 periph. So do it ourselves...
	
	// 6. Set FRF bit in SPI_CR2 to select TI protocol for serial comms if needed
	// Let's use SPI Motorola mode for now as we seem to have more control over polarity
	
	// 7. Select MSTR and SPE bits. They will remain set only if NSS pin is connected to a high level signal. MOSI  is out MISO in.
	SPI1->CR1 |= SPI_CR1_MSTR;  // SPI as master mode
	SPI1->CR1 |= SPI_CR1_SPE; // enable SPI!
}

void spi_close(void)
{}
	
void spi_read(void)
{}
	
void spi_write(void)
{
	// Transmit begins when a byte is written in the Tx buffer
	unsigned char myFirstByte = 0xA6;
	
	// TXE flag is set when data goes to shift register from Tx buffer. And interrupt
	// fired if TXEIE bit is set in SPI_CR2
	
	SPI1->DR = myFirstByte; // of it goes!
	
	volatile static int a = 5;
}
	
void spi_ioctl(void)
{}
