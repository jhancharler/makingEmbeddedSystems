#ifndef MY_RCC_H_INCLUDED
#define MY_RCC_H_INCLUDED

#include <stdint.h>
#include "MyBitMacros.h"

typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G,
	PORT_H,
	PORT_I,
	PORT_J,
	PORT_K,
} GPIO_Port;

typedef struct RCC
{
	volatile uint32_t reserved[12];
	volatile uint32_t RCC_AHB1ENR;
} RCC;

#define RCC_BASE		(0x40023800)
#define RCC_REG			((RCC*)(RCC_BASE))

#define ENABLE_PORTD_CLOCK() (SET_BIT(RCC_REG->RCC_AHB1ENR, PORT_D))
#define ENABLE_PORTA_CLOCK() (SET_BIT(RCC_REG->RCC_AHB1ENR, PORT_A))

#endif
