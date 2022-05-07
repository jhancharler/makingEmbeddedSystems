#include "MyGpio.h"
#include "MyBitMacros.h"
#include <assert.h>

// Initialise GPIO by setting its mode (input, output etc.)
void initGPIO(GPIO_typedef* gpio_port, gpio_pins_e pin, MODER_e mode)
{
	// Select mode for GPIO
	MODIFY_REG(gpio_port->MODER, 0x3UL << (pin * 2), mode << (pin * 2));
}

// Toggles a GPIO pin on a specific port.
void toggleGPIO(GPIO_typedef* gpio, gpio_pins_e gpioPin)
{
	TOGGLE_BIT(gpio->ODR, gpioPin);
}

// Either turns on or off a GPIO pin
void enableGPIO(GPIO_typedef* gpio, gpio_pins_e gpioPin, GPIO_State_e enable)
{
	assert(IS_GPIO_PIN(gpioPin));
	if (!enable)
	{
		SET_BIT(gpio->BSRR, gpioPin + 16);  // clear is upper 16 bits
	}
	else
	{
		SET_BIT(gpio->BSRR, gpioPin);
	}
}

// Reads the state of the GPIO pin (returns 1 if high or 0 if low).
GPIO_State_e readGPIO(GPIO_typedef* gpio, gpio_pins_e gpioPin)
{
	if (READ_BIT(gpio->IDR, gpioPin))
	{
		return GPIO_HIGH;
	}
	return GPIO_LOW;
}
