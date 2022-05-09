#ifndef MY_EXTI_INCLUDED
#define MY_EXTI_INCLUDED

#include "io_pin_definitions.h"

typedef enum IRQ_Trigger_e
{
	IRQ_RISING = 0x1,
	IRQ_FALLING = 0x2,
	IRQ_BOTH = 0x3
} IRQ_Trigger_e;

void enableGpioIRQ(GPIO_PORT_e gpio_port, GPIO_PIN_e gpio_pin, IRQ_Trigger_e fallingOrRising);
void disableGpioIRQ(GPIO_PORT_e gpio_port, GPIO_PIN_e gpio_pin);
void triggerSWInterrupt(GPIO_PIN_e pin);
void clearPendingInterrupt(GPIO_PIN_e pin);

#endif
