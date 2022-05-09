#include <stm32f407xx.h>

#include "MyEXTI.h"
#include "MyBitMacros.h"

// Maps GPIO pin number to the appropriate SYSCFG EXTICRx mask
static uint32_t _sysCfgMaskMap[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = SYSCFG_EXTICR1_EXTI0,
	[GPIO_PIN_1] = SYSCFG_EXTICR1_EXTI1,
	[GPIO_PIN_2] = SYSCFG_EXTICR1_EXTI2,
	[GPIO_PIN_3] = SYSCFG_EXTICR1_EXTI3,
	[GPIO_PIN_4] = SYSCFG_EXTICR2_EXTI4,
	[GPIO_PIN_5] = SYSCFG_EXTICR2_EXTI5,
	[GPIO_PIN_6] = SYSCFG_EXTICR2_EXTI6,
	[GPIO_PIN_7] = SYSCFG_EXTICR2_EXTI7,
	[GPIO_PIN_8] = SYSCFG_EXTICR3_EXTI8,
	[GPIO_PIN_9] = SYSCFG_EXTICR3_EXTI9,
	[GPIO_PIN_10] = SYSCFG_EXTICR3_EXTI10,
	[GPIO_PIN_11] = SYSCFG_EXTICR3_EXTI11,
	[GPIO_PIN_12] = SYSCFG_EXTICR4_EXTI12,
	[GPIO_PIN_13] = SYSCFG_EXTICR4_EXTI13,
	[GPIO_PIN_14] = SYSCFG_EXTICR4_EXTI14,
	[GPIO_PIN_15] = SYSCFG_EXTICR4_EXTI15,
};

// Maps GPIO pin number to the appropriate EXTI controller
static IRQn_Type _IRQnMap[GPIO_PINS_TOTAL] = 
{
	[GPIO_PIN_0] = EXTI0_IRQn,
	[GPIO_PIN_1] = EXTI1_IRQn,
	[GPIO_PIN_2] = EXTI2_IRQn,
	[GPIO_PIN_3] = EXTI3_IRQn,
	[GPIO_PIN_4] = EXTI4_IRQn,
	[GPIO_PIN_5] = EXTI9_5_IRQn,
	[GPIO_PIN_6] = EXTI9_5_IRQn,
	[GPIO_PIN_7] = EXTI9_5_IRQn,
	[GPIO_PIN_8] = EXTI9_5_IRQn,
	[GPIO_PIN_9] = EXTI9_5_IRQn,
	[GPIO_PIN_10] = EXTI15_10_IRQn,
	[GPIO_PIN_11] = EXTI15_10_IRQn,
	[GPIO_PIN_12] = EXTI15_10_IRQn,
	[GPIO_PIN_13] = EXTI15_10_IRQn,
	[GPIO_PIN_14] = EXTI15_10_IRQn,
	[GPIO_PIN_15] = EXTI15_10_IRQn,
};

// Enables IRQ on one of the 16 GPIO lines on any of the ports (A-H)
void enableGpioIRQ(GPIO_PORT_e gpio_port, GPIO_PIN_e gpio_pin, IRQ_Trigger_e fallingOrRising)
{
	uint32_t pinMask = (1UL << gpio_pin); // get pin mask for later use
	// Configure IRQ first, edge detection and syscfg clock enable
	EXTI->RTSR &= ~pinMask;  // clear rising
	if (fallingOrRising & IRQ_RISING)
	{
		
		EXTI->RTSR |= pinMask;  // set rising
	}
	// falling
	EXTI->FTSR &= pinMask;  // clear falling
	if (fallingOrRising & IRQ_FALLING)
	{
		EXTI->FTSR |= pinMask;  // set falling
	}
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;  // syscfg clock
	
	// configure SYSCFG so it knows where to expect the interrupt
	// pins 0 to 3 are EXTICR1 [0]  | pins 4 to 7 are EXTICR2 [1]
	// pins 8 to 11 are EXTICR3 [2] | pins 12 to 15 are EXTICR4 [3]
	unsigned char index = gpio_pin % 4;
	MODIFY_REG(SYSCFG->EXTICR[index], _sysCfgMaskMap[gpio_pin], (gpio_port << (4 * index)));
	
	// configuration done, let's enable interrupt now
	// Enable interrupt
	EXTI->IMR |= pinMask;
	NVIC_EnableIRQ(_IRQnMap[gpio_pin]);  // enable the IRQ on NVIC
}

void disableGpioIRQ(GPIO_PORT_e gpio_port, GPIO_PIN_e gpio_pin)
{
	uint32_t pinMask = (1UL << gpio_pin); // get pin mask for later use
	// Configure IRQ first, edge detection and syscfg clock enable
	EXTI->RTSR &= ~pinMask;  // clear rising
	EXTI->FTSR &= pinMask;  // clear falling
	
	// configure SYSCFG so it knows where to expect the interrupt
	// pins 0 to 3 are EXTICR1 [0]  | pins 4 to 7 are EXTICR2 [1]
	// pins 8 to 11 are EXTICR3 [2] | pins 12 to 15 are EXTICR4 [3]
	unsigned char index = gpio_pin % 4;
	SYSCFG->EXTICR[index] &= ~(_sysCfgMaskMap[gpio_pin]);
	
	// disable interrupt
	EXTI->IMR &= ~pinMask;
	// disable on nvic
	NVIC_DisableIRQ(_IRQnMap[gpio_pin]);
}

void triggerSWInterrupt(GPIO_PIN_e pin)
{
	EXTI->SWIER |= (0x1UL << pin);
}

void clearPendingInterrupt(GPIO_PIN_e pin)
{
	// write 1 to clear it (yes, 1)
	EXTI->PR |= (1UL << pin);
}
