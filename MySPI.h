#ifndef MY_SPI_INCLUDED
#define MY_SPI_INCLUDED

#include <stdint.h>

typedef struct SpiTransfer_s
{
	uint8_t* txBuf;
	uint8_t* rxBuf;
	uint32_t bytesToXferReceive;
} SpiTransfer_s;

void spi_open(void);
void spi_close(void);
void spi_read_write(SpiTransfer_s* transfer);
void spi_ioctl(void);

#endif
