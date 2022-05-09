#ifndef IO_PIN_DEFINITIONS_INCLUDED
#define IO_PIN_DEFINITIONS_INCLUDED

// GPIO State definitions
typedef enum GPIO_STATE_e
{
	GPIO_STATE_LOW = 0x0UL,
	GPIO_STATE_HIGH
} GPIO_STATE_e;

// GPIO Port definitions
typedef enum GPIO_PORT_e
{
	GPIO_PORT_A = 0x0UL,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_F,
	GPIO_PORT_G,
	GPIO_PORT_H,
	GPIO_PORTS_TOTAL
} GPIO_PORT_e;

// GPIO pin definitions
typedef enum GPIO_PIN_e
{
	GPIO_PIN_0 = 0x0UL,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
	GPIO_PINS_TOTAL
} GPIO_PIN_e;

// Register settings

// GPIO pupd definitions
typedef enum GPIO_PUPD_e
{
	GPIO_PUPD_NONE = 0x00UL,
	GPIO_PUPD_UP = 0x01UL,
	GPIO_PUPD_DOWN = 0x02UL,
} GPIO_PUPD_e;

// GPIO mode definitions
typedef enum GPIO_MODE_e
{
	GPIO_MODE_INPUT = 0x00UL,
	GPIO_MODE_OUTPUT = 0x01UL,
} GPIO_MODE_e;

// The GPIO type
typedef struct GPIO_type
{
	GPIO_PORT_e port;
	GPIO_PIN_e pin;
	GPIO_MODE_e mode;
	GPIO_PUPD_e pupdown;
} GPIO_type;

#endif
