#include "MyLIS3DSH.h"
#include "LIS3DSH_REGISTERS.h"
#include "MyClock.h"
#include "MySPI.h"
#include "MyBitMacros.h"

// Useful Macros
#define WHO_AM_I_DEFAULT	0x3F
#define MAX_16_BIT_SIGNED	0x7FFF
// Inline functions
#define COMBINE_8_BITS(msb, lsb) ((((uint16_t)(msb) << 8)) | (lsb))
#define CONVERT_ACCEL_TO_DOUBLE(val)	((((double)(val)) / (MAX_16_BIT_SIGNED)) * 2)

static uint8_t spiRxBuf[1024];
static uint8_t spiTxBuf[1024];

static SpiTransfer_s spiTransfer =
{
	.txBuf = spiTxBuf,
	.rxBuf = spiRxBuf,
	.bytesToXferReceive = 0
};

typedef enum ErrorCode_e
{
	EC_SUCCESS,
	EC_SPI_ERROR,
} ErrorCode_e;

/*
* @brief Writes 1 byte to accelerometer register
* @details Assumes SPI is initialised .Sends 1 byte register, 1 byte data
* @params uint8_t reg - register to write to on accel
* @params uint8_t value - data to write
* @return	0 if no error
*/
static int lis3dsh_write_reg(uint8_t reg, uint8_t value)
{
	MY_CLEAR_BIT(reg, 7); // MSB 0 means write
	spiTransfer.bytesToXferReceive = 2;
	spiTransfer.txBuf[0] = reg;
	spiTransfer.txBuf[1] = value;
	spi_read_write(&spiTransfer);	// x20 x67

	return EC_SUCCESS;
}

static int lis3dsh_read_reg(uint8_t reg, uint8_t* value)
{
	MY_SET_BIT(reg, 7); // MSB 1 means reads
	spiTransfer.bytesToXferReceive = 2;
	spiTransfer.txBuf[0] = reg;
	spi_read_write(&spiTransfer);
	*value = spiTransfer.rxBuf[1];
	return EC_SUCCESS;
}

/*
@brief Initialises accelerometer

TODO: Improve init parameters. Choose SPI? for example? Perhaps let it init SPI itself?
*/
void accel_lis3dsh_init(void)
{
	spi_open();

	// Wait 5ms for boot procedure to complete
	while(msPassedSinceBoot() < 5);

	// Check if alive
	uint8_t whoAmI = 0;
	lis3dsh_read_reg(LIS3DSH_WHO_AM_I, &whoAmI);

	if (whoAmI != WHO_AM_I_DEFAULT)
	{
		volatile int a = 1;
	}

	// Select at least 1 operating mode

	// turn on axes and datarate
	// 0x20 0x67
	lis3dsh_write_reg(LIS3DSH_CTRL_REG4,
		(CTRL_REG_4_XEN | CTRL_REG_4_YEN | CTRL_REG_4_ZEN | CTRL_REG_4_ODR_100_HZ));
}

/*
* @brief Reads latest accelerometer data
* @detail
* @param uin16_t* out_x - x location accel data
* @param uin16_t* out_y - y location accel data
* @param uin16_t* out_z - z location accel data
* @return error code
*/
int accel_lis3dsh_read_data(AccelData* data)
{
	uint8_t temp;
	int16_t temp16;	// accel data is 2s complement (signed)
	uint8_t dataL, dataH;
	uint8_t accelOutReg = LIS3DSH_OUT_X_L;
	do	// while no data available
	{
		lis3dsh_read_reg(LIS3DSH_STATUS, &temp);
	} while ( (temp & STATUS_ZYXOR) == 0 );
	// read from the output registers
	// x
	lis3dsh_read_reg(accelOutReg++, &dataL);
	lis3dsh_read_reg(accelOutReg++, &dataH);
	temp16 = COMBINE_8_BITS(dataH, dataL);
	data->x_pos = CONVERT_ACCEL_TO_DOUBLE(temp16);
	// y
	lis3dsh_read_reg(accelOutReg++, &dataL);
	lis3dsh_read_reg(accelOutReg++, &dataH);
	temp16 = COMBINE_8_BITS(dataH, dataL);
	data->y_pos = CONVERT_ACCEL_TO_DOUBLE(temp16);
	// z
	lis3dsh_read_reg(accelOutReg++, &dataL);
	lis3dsh_read_reg(accelOutReg++, &dataH);
	temp16 = COMBINE_8_BITS(dataH, dataL);
	data->z_pos =  CONVERT_ACCEL_TO_DOUBLE(temp16);

	return EC_SUCCESS;
}
