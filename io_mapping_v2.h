#ifndef IO_MAPPING_V1_INCLUDED
#define IO_MAPPING_V1_INCLUDED

#include "MyGpio.h"
#include "MyRCC.h"

// Board peripheral clocks
#define ENABLE_LED_CLOCK()	ENABLE_PORTD_CLOCK()
#define ENABLE_BTN_CLOCK()	ENABLE_PORTA_CLOCK()

// Peripheral ports
#define LED_PORT					GPIOD
#define BTN_PORT					GPIOA

typedef gpio_pins_e LEDS_e;
typedef gpio_pins_e BTNS_e;
typedef GPIO_State_e ButtonState_e;
typedef GPIO_State_e LEDState_e;

// Peripheral pins
#define LED_GREEN 	GPIO_PIN_12
#define LED_ORANGE 	GPIO_PIN_13
#define LED_RED 		GPIO_PIN_14
#define LED_BLUE 		GPIO_PIN_15

#define BTN_USR1		GPIO_PIN_0

// Button state
#define BUTTON_PRESSED	GPIO_HIGH
#define BUTTON_RELEASED	GPIO_LOW

// LED state
#define LED_ON	GPIO_HIGH
#define LED_OFF	GPIO_LOW

#endif
