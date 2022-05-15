#include <stm32f407xx.h>
#include "io_handler.h"
#include "MyBitMacros.h"
#include <assert.h>

// Port map
static GPIO_TypeDef* _gpioPorts[GPIO_PORTS_TOTAL] =
{
	[GPIO_PORT_A] = GPIOA,
	[GPIO_PORT_B] = GPIOB,
	[GPIO_PORT_C] = GPIOC,
	[GPIO_PORT_D] = GPIOD,
	[GPIO_PORT_E] = GPIOE,
	[GPIO_PORT_F] = GPIOF,
	[GPIO_PORT_G] = GPIOG,
	[GPIO_PORT_H] = GPIOH,
};

// Mode mask map
static uint32_t _gpioModeMasks[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = GPIO_MODER_MODER0,
	[GPIO_PIN_1] = GPIO_MODER_MODER1,
	[GPIO_PIN_2] = GPIO_MODER_MODER2,
	[GPIO_PIN_3] = GPIO_MODER_MODER3,
	[GPIO_PIN_4] = GPIO_MODER_MODER4,
	[GPIO_PIN_5] = GPIO_MODER_MODER5,
	[GPIO_PIN_6] = GPIO_MODER_MODER6,
	[GPIO_PIN_7] = GPIO_MODER_MODER7,
	[GPIO_PIN_8] = GPIO_MODER_MODER8,
	[GPIO_PIN_9] = GPIO_MODER_MODER9,
	[GPIO_PIN_10] = GPIO_MODER_MODER10,
	[GPIO_PIN_11] = GPIO_MODER_MODER11,
	[GPIO_PIN_12] = GPIO_MODER_MODER12,
	[GPIO_PIN_13] = GPIO_MODER_MODER13,
	[GPIO_PIN_14] = GPIO_MODER_MODER14,
	[GPIO_PIN_15] = GPIO_MODER_MODER15,
};

// PUPDR mask map
static uint32_t _gpioPUPDRMasks[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = GPIO_PUPDR_PUPD0,
	[GPIO_PIN_1] = GPIO_PUPDR_PUPD1,
	[GPIO_PIN_2] = GPIO_PUPDR_PUPD2,
	[GPIO_PIN_3] = GPIO_PUPDR_PUPD3,
	[GPIO_PIN_4] = GPIO_PUPDR_PUPD4,
	[GPIO_PIN_5] = GPIO_PUPDR_PUPD5,
	[GPIO_PIN_6] = GPIO_PUPDR_PUPD6,
	[GPIO_PIN_7] = GPIO_PUPDR_PUPD7,
	[GPIO_PIN_8] = GPIO_PUPDR_PUPD8,
	[GPIO_PIN_9] = GPIO_PUPDR_PUPD9,
	[GPIO_PIN_10] = GPIO_PUPDR_PUPD10,
	[GPIO_PIN_11] = GPIO_PUPDR_PUPD11,
	[GPIO_PIN_12] = GPIO_PUPDR_PUPD12,
	[GPIO_PIN_13] = GPIO_PUPDR_PUPD13,
	[GPIO_PIN_14] = GPIO_PUPDR_PUPD14,
	[GPIO_PIN_15] = GPIO_PUPDR_PUPD15,
};

// GPIO BSRR SET MAP 
static uint32_t _gpioBSRRSetMask[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = GPIO_BSRR_BS0,
	[GPIO_PIN_1] = GPIO_BSRR_BS1,
	[GPIO_PIN_2] = GPIO_BSRR_BS2,
	[GPIO_PIN_3] = GPIO_BSRR_BS3,
	[GPIO_PIN_4] = GPIO_BSRR_BS4,
	[GPIO_PIN_5] = GPIO_BSRR_BS5,
	[GPIO_PIN_6] = GPIO_BSRR_BS6,
	[GPIO_PIN_7] = GPIO_BSRR_BS7,
	[GPIO_PIN_8] = GPIO_BSRR_BS8,
	[GPIO_PIN_9] = GPIO_BSRR_BS9,
	[GPIO_PIN_10] = GPIO_BSRR_BS10,
	[GPIO_PIN_11] = GPIO_BSRR_BS11,
	[GPIO_PIN_12] = GPIO_BSRR_BS12,
	[GPIO_PIN_13] = GPIO_BSRR_BS13,
	[GPIO_PIN_14] = GPIO_BSRR_BS14,
	[GPIO_PIN_15] = GPIO_BSRR_BS15,
};

// GPIO BSRR RESET MAP 
static uint32_t _gpioBSRRResetMask[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = GPIO_BSRR_BR0,
	[GPIO_PIN_1] = GPIO_BSRR_BR1,
	[GPIO_PIN_2] = GPIO_BSRR_BR2,
	[GPIO_PIN_3] = GPIO_BSRR_BR3,
	[GPIO_PIN_4] = GPIO_BSRR_BR4,
	[GPIO_PIN_5] = GPIO_BSRR_BR5,
	[GPIO_PIN_6] = GPIO_BSRR_BR6,
	[GPIO_PIN_7] = GPIO_BSRR_BR7,
	[GPIO_PIN_8] = GPIO_BSRR_BR8,
	[GPIO_PIN_9] = GPIO_BSRR_BR9,
	[GPIO_PIN_10] = GPIO_BSRR_BR10,
	[GPIO_PIN_11] = GPIO_BSRR_BR11,
	[GPIO_PIN_12] = GPIO_BSRR_BR12,
	[GPIO_PIN_13] = GPIO_BSRR_BR13,
	[GPIO_PIN_14] = GPIO_BSRR_BR14,
	[GPIO_PIN_15] = GPIO_BSRR_BR15,
};

// GPIO pin mask
static uint32_t _gpioPinMask[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = (0x1UL << GPIO_PIN_0),
	[GPIO_PIN_1] = (0x1UL << GPIO_PIN_1),
	[GPIO_PIN_2] = (0x1UL << GPIO_PIN_2),
	[GPIO_PIN_3] = (0x1UL << GPIO_PIN_3),
	[GPIO_PIN_4] = (0x1UL << GPIO_PIN_4),
	[GPIO_PIN_5] = (0x1UL << GPIO_PIN_5),
	[GPIO_PIN_6] = (0x1UL << GPIO_PIN_6),
	[GPIO_PIN_7] = (0x1UL << GPIO_PIN_7),
	[GPIO_PIN_8] = (0x1UL << GPIO_PIN_8),
	[GPIO_PIN_9] = (0x1UL << GPIO_PIN_9),
	[GPIO_PIN_10] = (0x1UL << GPIO_PIN_10),
	[GPIO_PIN_11] = (0x1UL << GPIO_PIN_11),
	[GPIO_PIN_12] = (0x1UL << GPIO_PIN_12),
	[GPIO_PIN_13] = (0x1UL << GPIO_PIN_13),
	[GPIO_PIN_14] = (0x1UL << GPIO_PIN_14),
	[GPIO_PIN_15] = (0x1UL << GPIO_PIN_15),
};


// Initialises GPIO as input or output, with or without pullup/down
void gpio_init(GPIO_type gpio)
{
	// TODO, check args?
	
	// get handles and masks
	GPIO_TypeDef* ioPort = _gpioPorts[gpio.port];  // get handle to IO port
  uint32_t modeMask = _gpioModeMasks[gpio.pin];  // get value of mode mask
	uint32_t modeNewValue = gpio.mode << (gpio.pin * 2);
	
	// configure mode
	MODIFY_REG(ioPort->MODER, modeMask, modeNewValue);
	
	// configure pull-up/down if input
	if (gpio.mode == GPIO_MODE_INPUT)
	{
		uint32_t pupdrMask = _gpioPUPDRMasks[gpio.pin];
		uint32_t pupdrNewValue = gpio.pupdown << (gpio.pin * 2);
		MODIFY_REG(ioPort->PUPDR, pupdrMask, pupdrNewValue);
	}

	if (gpio.mode == GPIO_MODE_AF)
	{
		uint8_t AFIndex = gpio.pin > GPIO_PIN_7 ? 1 : 0;  // get lower or higher AF register as needed
		uint8_t AFShift = (gpio.pin % 8) * 4;
		ioPort->AFR[AFIndex] |= (gpio.AFValue << AFShift);	// set AF for the pin we want to use
	}
}

// Enables or disables an output GPIO
void gpio_enable(GPIO_STATE_e state, GPIO_PORT_e port, GPIO_PIN_e pin)
{
	if (state == GPIO_STATE_LOW)
	{
		_gpioPorts[port]->BSRR |= _gpioBSRRResetMask[pin];  // GPIO 0
	}
	else
	{
		_gpioPorts[port]->BSRR |= _gpioBSRRSetMask[pin];  // GPIO 1
	}
}

// Toggles given GPIO
void gpio_toggle(GPIO_PORT_e port, GPIO_PIN_e pin)
{
	_gpioPorts[port]->ODR ^= _gpioPinMask[pin];
}

// Reads input gpio, returns level
GPIO_STATE_e gpio_read(GPIO_PORT_e port, GPIO_PIN_e pin)
{
	if((_gpioPorts[port]->IDR & _gpioPinMask[pin]) == _gpioPinMask[pin])
	{
		return GPIO_STATE_HIGH;
	}
	return GPIO_STATE_LOW;
}

// Enables clock for GPIO
void rcc_enable_gpio_port_clock(GPIO_PORT_e port)
{
	RCC->AHB1ENR |= (1UL << port);
}
