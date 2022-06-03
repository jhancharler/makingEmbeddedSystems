#ifndef MY_LIS3DSH_H_INCLUDED
#define MY_LIS3DSH_H_INCLUDED

#include <stdint.h>

typedef struct AccelData
{
    double x_pos;
    double y_pos;
    double z_pos;
} AccelData;

void accel_lis3dsh_init(void);
int accel_lis3dsh_read_data(AccelData* data);
int accel_lis3dsh_read_data_DMA(uint32_t size);

#endif
