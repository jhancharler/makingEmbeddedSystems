#ifndef IO_MAPPING_V1_INCLUDED
#define IO_MAPPING_V1_INCLUDED

#include "MyGpio.h"
#include "MyRCC.h"

#define ENABLE_LED_CLOCK()	ENABLE_PORTD_CLOCK()

#define LED_PORT					GPIOD
#define BTN_PORT					GPIOA

typedef gpio_pins_e LEDS_e;
typedef gpio_pins_e BTNS_e;

#define LED_GREEN 	GPIO_PIN_15
#define LED_ORANGE 	GPIO_PIN_14
#define LED_RED 		GPIO_PIN_13
#define LED_BLUE 		GPIO_PIN_12

#define BTN_USR			GPIO_PIN_0

#endif
