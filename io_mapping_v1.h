#ifndef IO_MAPPING_V1_INCLUDED
#define IO_MAPPING_V1_INCLUDED

#include "io_pin_definitions.h"

// LEDs
#define LED_PORT 				GPIO_PORT_D
#define LED_GREEN_PIN  	GPIO_PIN_12
#define LED_ORANGE_PIN 	GPIO_PIN_13
#define LED_RED_PIN  		GPIO_PIN_14
#define LED_BLUE_PIN  	GPIO_PIN_15

// LED PWM timers and channels
#define LED_GREEN_TIM							Timer_TIM4
#define LED_GREEN_TIM_CHANNEL			Timer_Chan_1
#define LED_GREEN_TIM_AF					AF2
#define LED_ORANGE_TIM						Timer_TIM4
#define LED_ORANGE_TIM_CHANNEL		Timer_Chan_2
#define LED_ORANGE_AF							AF2
#define LED_RED_TIM								Timer_TIM4
#define LED_RED_TIM_CHANNEL				Timer_Chan_3
#define LED_RED_AF								AF2
#define LED_BLUE_TIM							Timer_TIM4
#define LED_BLUE_TIM_CHANNEL			Timer_Chan_4
#define LED_BLUE_AF								AF2

// Buttons
#define BTN_USR_PORT  	GPIO_PORT_A
#define BTN_USR_PIN  		GPIO_PIN_0

#endif
