#include <stm32f407xx.h>
#include "MyClock.h"

static volatile ticks_t sysemTicks = 0;

void initPeriodicSystemClocks(void)
{
	// Enable system clock
	SysTick_Config(SystemCoreClock / 1000);  // tick every ms
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;   // 5 secs periodic

	// tim1
	TIM1->CR1 &= ~TIM_CR1_CEN;  // disable timer
	TIM1->PSC = 16000; // tim1 period, runs every 1 second
	TIM1->EGR |= TIM_EGR_UG;  // generate update event to load prescaler
	clearUpdate(); // since we set the PSC, event will be triggered, clear it
	TIM1->ARR = 500;
	TIM1->CNT = 0;
	TIM1->DIER |= TIM_DIER_UIE;  // enable interrupt on update
	TIM1->CR1 |= TIM_CR1_URS;  // only counter over/underflow generates irq or dma req if en
	
	// enable timers
	TIM1->CR1 |= TIM_CR1_CEN;

	// enable irq
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

void startTimer2(void)
{
	// Enable system clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   // 2 seconds single shot

	// tim2
	TIM2->PSC = 16000;
	TIM2->EGR |= TIM_EGR_UG;  // generate update event to load prescaler
	clearUpdateTim2();
	TIM2->ARR = 1000;  // runs for 1 seconds
	TIM2->CNT = 0;

	TIM2->CR1 |= TIM_CR1_OPM;  // one pulse mode
	TIM2->DIER |= TIM_DIER_UIE;  // allow irq
	TIM2->CR1 |= TIM_CR1_URS;  // update request source only on overflow
	
	TIM2->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM2_IRQn);
}

uint8_t updateHappened(void)
{
	return TIM1->SR & TIM_SR_UIF;
}

void clearUpdate(void)
{
	TIM1->SR &= ~TIM_SR_UIF;
}

void clearUpdateTim2(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
}

void delayMs(ticks_t ms)
{
	ticks_t then = sysemTicks;
	while (timeSince(then) < ms);
}

ticks_t timeSince(ticks_t then)
{
	return sysemTicks - then;  // todo, check for rollover, though is it needed?
}

ticks_t sysClock(void)
{
	return sysemTicks;
}

void SysTick_Handler(void)
{
	sysemTicks++;
}
