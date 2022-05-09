// This header is responsible for initialising GPIO
// input and output

#ifndef IO_HANDLER_INCLUDED
#define IO_HANDLER_INCLUDED

#include "io_pin_definitions.h"

// GPIO Functions
void gpio_init(GPIO_type gpio);

// GPIO Output
void gpio_enable(GPIO_STATE_e state, GPIO_PORT_e port, GPIO_PIN_e pin);
void gpio_toggle(GPIO_PORT_e port, GPIO_PIN_e pin);

// GPIO Input
GPIO_STATE_e gpio_read(GPIO_PORT_e port, GPIO_PIN_e pin);

// GPIO clocks
void rcc_enable_gpio_port_clock(GPIO_PORT_e port);

// Exported macros
#define VAL_IS_BETWEEN_INC(val, min, max)	(((val) <= max) && (val>= min))

#define IS_GPIO_PIN(pin) 		(VAL_IS_BETWEEN_INC((pin), 	GPIO_PIN_0, 			GPIO_PIN_15))
#define IS_GPIO_PORT(port) 	(VAL_IS_BETWEEN_INC((port), GPIO_PORT_A, 			GPIO_PORT_H))
#define IS_GPIO_MODE(mode)	(VAL_IS_BETWEEN_INC((mode), GPIO_MODE_INPUT, 	GPIO_MODE_OUTPUT))

#endif
