#include <stm32f407xx.h>
#include "MyClock.h"

static volatile ticks_t sysemTicks = 0;
static uint8_t initialisedAtLeastOnce = 0;

void initSystemClock(clockFrequency_e frequency)
{
	if (initialisedAtLeastOnce == 0)
	{
		SysTick_Config(SystemCoreClock / 1000);  // tick every ms
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	
	TIM1->CR1 &= ~TIM_CR1_CEN;  // disable timer
	
	if (frequency == CLOCK_FQ_17)  // want it to tick every 17 Hz
	{
		TIM1->ARR = (1046);
		TIM1->PSC = (900);
		TIM1->CNT = 0; // reset count
	}
	else if (frequency == CLOCK_FQ_13) // else 13 Hz
	{
		TIM1->ARR = (1758);
		TIM1->PSC = (700);
		TIM1->CNT = 0; // reset count
	}
	else
	{
		// shouldn't come here
	}
	
	if (initialisedAtLeastOnce == 0)
	{
		TIM1->DIER |= TIM_DIER_UIE;  // enable interrupt on update
		NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	}
	
	TIM1->CR1 |= TIM_CR1_CEN;  // enable timer
	initialisedAtLeastOnce = 1;
}

uint8_t updateHappened(void)
{
	return TIM1->SR & TIM_SR_UIF;
}

void clearUpdate(void)
{
	TIM1->SR &= ~TIM_SR_UIF;
}

ticks_t sysClock(void)
{
	return sysemTicks;
}

void SysTick_Handler(void)
{
	sysemTicks++;
}
