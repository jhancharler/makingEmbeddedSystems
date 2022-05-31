#ifndef LIS3DSH_REGISTERS_INCLUDED
#define LIS3DSH_REGISTERS_INCLUDED

// Todo: Comment below to improve readability. 
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
// Constant shift registers (state machien only)
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
#define LIS3DSH_VFC_1 0x1B
#define LIS3DSH_VFC_2 0x1C
#define LIS3DSH_VFC_3 0x1D
#define LIS3DSH_VFC_4 0x1E
#define LIS3DSH_THRS3 0x1F
#define LIS3DSH_CTRL_REG4 0x20
#define LIS3DSH_CTRL_REG1 0x21
#define LIS3DSH_CTRL_REG2 0x22
#define LIS3DSH_CTRL_REG3 0x23
#define LIS3DSH_CTRL_REG5 0x24
#define LIS3DSH_CTRL_REG6 0x25
#define LIS3DSH_STATUS 0x27
#define LIS3DSH_OUT_X_L 0x28
#define LIS3DSH_OUT_X_H 0x29
#define LIS3DSH_OUT_Y_L 0x2A
#define LIS3DSH_OUT_Y_H 0x2B
#define LIS3DSH_OUT_Z_L 0x2C
#define LIS3DSH_OUT_Z_H 0x2D
#define LIS3DSH_FIFO_CTRL 0x2E
#define LIS3DSH_FIFO_SRC 0x2F
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
#define LIS3DSH_TIM4_1 0x50
#define LIS3DSH_TIM3_1 0x51
#define LIS3DSH_TIM2_1_L 0x52
#define LIS3DSH_TIM2_1_H 0x53
#define LIS3DSH_TIM1_1_L 0x54
#define LIS3DSH_TIM1_1_H 0x54
#define LIS3DSH_THRS2_1 0x56
#define LIS3DSH_THRS1_1 0x57
#define LIS3DSH_MASK1_B 0x59
#define LIS3DSH_MASK1_A 0x5A
#define LIS3DSH_SETT1 0x5B
#define LIS3DSH_PR1 0x5C
#define LIS3DSH_TC1_L 0x5D
#define LIS3DSH_TC1_H 0x5E
#define LIS3DSH_OUTS1 0x5F
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
#define LIS3DSH_TIM4_2 0x70
#define LIS3DSH_TIM3_2 0x71
#define LIS3DSH_TIM2_2_L 0x72
#define LIS3DSH_TIM2_2_H 0x73
#define LIS3DSH_TIM1_2_L 0x74
#define LIS3DSH_TIM1_2_H 0x75
#define LIS3DSH_THRS2_2 0x76
#define LIS3DSH_THRS1_2 0x77
#define LIS3DSH_DES2 0x78
#define LIS3DSH_MASK2_B 0x79
#define LIS3DSH_MASK2_A 0x7A
#define LIS3DSH_SETT2 0x7B
#define LIS3DSH_PR2 0x7C
#define LIS3DSH_TC2_H 0x7D
#define LIS3DSH_TC2_H 0x7E
#define LIS3DSH_OUTS2 0x7F

#endif