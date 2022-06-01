#ifndef LIS3DSH_REGISTERS_INCLUDED
#define LIS3DSH_REGISTERS_INCLUDED

#include <stdint.h>

#define MY_BIT0	(1)
#define MY_BIT1	(2)
#define MY_BIT2	(4)
#define MY_BIT3	(8)

// Perform accel_init. Do unix style pattern?
// Improve SPI driver as we progress.
// Goal is to see if accelerometer is working by checking z axis.

// SMx = State machine x (2 state machines exist)

// Temperature output register
#define LIS3DSH_OUT_T 0x0C
// Read-only info
#define LIS3DSH_INFO1 0x0D
#define LIS3DSH_INFO2 0x0E
// Who-am-i register
#define LIS3DSH_WHO_AM_I 0x0F
// Offset correction registers
#define LIS3DSH_OFF_X 0x10
#define LIS3DSH_OFF_Y 0x11
#define LIS3DSH_OFF_Z 0x12
// Constant shift registers (state machine only)
#define LIS3DSH_CS_X 0x13
#define LIS3DSH_CS_Y 0x14
#define LIS3DSH_CS_Z 0x15
// 16-bit long-counter register for interrupt state machine program timing
#define LIS3DSH_LC_L 0x16
#define LIS3DSH_LC_H 0x17
// Interrupt status - synch register
#define LIS3DSH_STAT 0x18
// Peak detection for SM1
#define LIS3DSH_PEAK1 0x19
// Peak detection for SM2
#define LIS3DSH_PEAK2 0x1A
// Vector coefficient registers
#define LIS3DSH_VFC_1 0x1B
#define LIS3DSH_VFC_2 0x1C
#define LIS3DSH_VFC_3 0x1D
#define LIS3DSH_VFC_4 0x1E
// Threshold value register
#define LIS3DSH_THRS3 0x1F
// Control register 4: ODR select, enable axis, output register update setting
#define LIS3DSH_CTRL_REG4 0x20
// Control register 1: SM1 control register
#define LIS3DSH_CTRL_REG1 0x21
// Control register 2: SM2 control register
#define LIS3DSH_CTRL_REG2 0x22
// Control register 3: Data ready, soft reset, interrupt settings etc.
#define LIS3DSH_CTRL_REG3 0x23
// Control register 5: self test, spi mode select, anti-alias, scale select
#define LIS3DSH_CTRL_REG5 0x24
// Control register 6: Force reboot, fifo settings
#define LIS3DSH_CTRL_REG6 0x25
// Status reg: data overrun, new data available flags
#define LIS3DSH_STATUS 0x27
// Accelerometer output buffers (16 bit)
#define LIS3DSH_OUT_X_L 0x28
#define LIS3DSH_OUT_X_H 0x29
#define LIS3DSH_OUT_Y_L 0x2A
#define LIS3DSH_OUT_Y_H 0x2B
#define LIS3DSH_OUT_Z_L 0x2C
#define LIS3DSH_OUT_Z_H 0x2D
// FIFO mode configure register
#define LIS3DSH_FIFO_CTRL 0x2E
// FIFO further settings: watermark, overrun, fifo empty, fifo stored data level
#define LIS3DSH_FIFO_SRC 0x2F
// State machine 1 opcodes register
#define LIS3DSH_ST1_1 0x40
#define LIS3DSH_ST2_1 0x41
#define LIS3DSH_ST3_1 0x42
#define LIS3DSH_ST4_1 0x43
#define LIS3DSH_ST5_1 0x44
#define LIS3DSH_ST6_1 0x45
#define LIS3DSH_ST7_1 0x46
#define LIS3DSH_ST8_1 0x47
#define LIS3DSH_ST9_1 0x48
#define LIS3DSH_ST10_1 0x49
#define LIS3DSH_ST11_1 0x4A
#define LIS3DSH_ST12_1 0x4B
#define LIS3DSH_ST13_1 0x4C
#define LIS3DSH_ST14_1 0x4D
#define LIS3DSH_ST15_1 0x4E
#define LIS3DSH_ST16_1 0x4F
// 8-bit and 16-bit general timers for SM1 operation.
#define LIS3DSH_TIM4_1 0x50
#define LIS3DSH_TIM3_1 0x51
#define LIS3DSH_TIM2_1_L 0x52
#define LIS3DSH_TIM2_1_H 0x53
#define LIS3DSH_TIM1_1_L 0x54
#define LIS3DSH_TIM1_1_H 0x54
// Threshold values used in SM1 operation
#define LIS3DSH_THRS2_1 0x56
#define LIS3DSH_THRS1_1 0x57
// Axis and sign masks for SM1: +/- disabled/enabled
#define LIS3DSH_MASK1_B 0x59
#define LIS3DSH_MASK1_A 0x5A
// Setting for SM1: threshold, peak detection, flags
#define LIS3DSH_SETT1 0x5B
// Program counter and reset pointer for motion-detection SM1
#define LIS3DSH_PR1 0x5C
// Another 16 bit general timer for SM1
#define LIS3DSH_TC1_L 0x5D
#define LIS3DSH_TC1_H 0x5E
// Output flags on axis for interrupt SM1 management
#define LIS3DSH_OUTS1 0x5F
// State machine 2 system registers.
#define LIS3DSH_ST1_2 0x60
#define LIS3DSH_ST2_2 0x61
#define LIS3DSH_ST3_2 0x62
#define LIS3DSH_ST4_2 0x63
#define LIS3DSH_ST5_2 0x64
#define LIS3DSH_ST6_2 0x65
#define LIS3DSH_ST7_2 0x66
#define LIS3DSH_ST8_2 0x67
#define LIS3DSH_ST9_2 0x68
#define LIS3DSH_ST10_2 0x69
#define LIS3DSH_ST11_2 0x6A
#define LIS3DSH_ST12_2 0x6B
#define LIS3DSH_ST13_2 0x6C
#define LIS3DSH_ST14_2 0x6D
#define LIS3DSH_ST15_2 0x6E
#define LIS3DSH_ST16_2 0x6F
// 8-bit and 16-bit general timers for SM2 operation.
#define LIS3DSH_TIM4_2 0x70
#define LIS3DSH_TIM3_2 0x71
#define LIS3DSH_TIM2_2_L 0x72
#define LIS3DSH_TIM2_2_H 0x73
#define LIS3DSH_TIM1_2_L 0x74
#define LIS3DSH_TIM1_2_H 0x75
// Threshold values used in SM2 operation
#define LIS3DSH_THRS2_2 0x76
#define LIS3DSH_THRS1_2 0x77
// Decimation counter value for SM2
#define LIS3DSH_DES2 0x78
// Axis and sign masks for SM2: +/- disabled/enabled
#define LIS3DSH_MASK2_B 0x79
#define LIS3DSH_MASK2_A 0x7A
// Setting for SM2: threshold, peak detection, flags
#define LIS3DSH_SETT2 0x7B
// Program counter and reset pointer for motion-detection SM2
#define LIS3DSH_PR2 0x7C
// Another 16 bit general timer for SM2
#define LIS3DSH_TC2_L 0x7D
#define LIS3DSH_TC2_H 0x7E
// Output flags on axis for interrupt SM2 management
#define LIS3DSH_OUTS2 0x7F

// Register masks
//
#define FIFO_CTRL_TMP0		(1UL << 0)
#define FIFO_CTRL_TMP1		(1UL << 1)
#define FIFO_CTRL_TMP2		(1UL << 2)
#define FIFO_CTRL_TMP3		(1UL << 3)
#define FIFO_CTRL_TMP4		(1UL << 4)
#define FIFO_CTRL_FMODE0	(1UL << 5)
#define FIFO_CTRL_FMODE1	(1UL << 6)
#define FIFO_CTRL_FMODE2	(1UL << 7)
//
#define CTRL_REG_4_XEN_Pos	(0U)
#define CTRL_REG_4_XEN_Msk	(1U << (CTRL_REG_4_XEN_Pos))
#define CTRL_REG_4_XEN			(CTRL_REG_4_XEN_Msk)
#define CTRL_REG_4_YEN_Pos	(1U)
#define CTRL_REG_4_YEN_Msk	(1U << (CTRL_REG_4_YEN_Pos))
#define CTRL_REG_4_YEN			(CTRL_REG_4_YEN_Msk)
#define CTRL_REG_4_ZEN_Pos	(2U)
#define CTRL_REG_4_ZEN_Msk	(1U << (CTRL_REG_4_ZEN_Pos))
#define CTRL_REG_4_ZEN			(CTRL_REG_4_ZEN_Msk)	
#define CTRL_REG_4_BDU_Pos	(3U)
#define CTRL_REG_4_BDU_Msk	(1U << (CTRL_REG_4_BDU_Pos))
#define CTRL_REG_4_BDU			(CTRL_REG_4_BDU_Msk)
#define CTRL_REG_4_ODR_Pos 	(4U)
#define CTRL_REG_4_ODR_Msk	(0xFU << (CTRL_REG_4_ODR_Pos))
#define CTRL_REG_4_ODR_0		(0x1U << (CTRL_REG_4_ODR_Pos))
#define CTRL_REG_4_ODR_1		(0x2U << (CTRL_REG_4_ODR_Pos))
#define CTRL_REG_4_ODR_2		(0x4U << (CTRL_REG_4_ODR_Pos))
#define CTRL_REG_4_ODR_3		(0x8U << (CTRL_REG_4_ODR_Pos))
#define CTRL_REG_4_ODR_PWRDN	(0U)
#define CTRL_REG_4_ODR_100_HZ	(CTRL_REG_4_ODR_1 | CTRL_REG_4_ODR_2)
//
#define STATUS_XDA_Pos (0U)
#define STATUS_XDA_Msk (1U << (STATUS_XDA_Pos))
#define STATUS_XDA	(STATUS_XDA_Msk)
#define STATUS_YDA_Pos (1U)
#define STATUS_YDA_Msk (1U << (STATUS_YDA_Pos))
#define STATUS_YDA	(STATUS_YDA_Msk)
#define STATUS_ZDA_Pos (2U)
#define STATUS_ZDA_Msk (1U << (STATUS_ZDA_Pos))
#define STATUS_ZDA	(STATUS_ZDA_Msk)
#define STATUS_ZYXDA_Pos ((3U)
#define STATUS_ZYXDA_Msk (1U << (STATUS_ZYXDA_Pos))
#define STATUS_ZYXDA	(STATUS_ZYXDA_Msk)
#define STATUS_XOR_Pos (4U)
#define STATUS_XOR_Msk (1U << (STATUS_XOR_Pos))
#define STATUS_XOR	(STATUS_XOR_Msk)
#define STATUS_YOR_Pos (5U)
#define STATUS_YOR_Msk (1U << (STATUS_YOR_Pos))
#define STATUS_YOR	(STATUS_YOR_Msk)
#define STATUS_ZOR_Pos (6U)
#define STATUS_ZOR_Msk (1U << (STATUS_ZOR_Pos))
#define STATUS_ZOR	(STATUS_ZOR_Msk)
#define STATUS_ZYXOR_Pos (7U)
#define STATUS_ZYXOR_Msk (1U << (STATUS_ZYXOR_Pos))
#define STATUS_ZYXOR	(STATUS_ZYXOR_Msk)

#endif
