#ifndef MY_SPI_INCLUDED
#define MY_SPI_INCLUDED

#include <stdint.h>

typedef struct SpiTransfer_s
{
	uint8_t* txBuf;
	uint8_t* rxBuf;
	uint8_t readOnly;
	uint32_t bytesToTransmit;
    uint32_t bytesToReceive;    // the highest of the above will be total xfer size
} SpiTransfer_s;

void spi_open(void);
void spi_close(void);
void spi_read_write(SpiTransfer_s* transfer);
void spi_ioctl(void);

uint32_t getSPI1RxReg(void);

#endif
