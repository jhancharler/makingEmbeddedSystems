#include "MyPWM.h"
#include "io_pin_definitions.h"
#include "stm32f407xx.h"
#include "MyBitMacros.h"
#include <stdint.h>

#define PWM_FQ 1000
#define GET_ARR_VALUE() (SystemCoreClock / PWM_FQ)

static TIM_TypeDef* const TIMERS[] = 
{
	[Timer_TIM2] = TIM2,
	[Timer_TIM3] = TIM3,
	[Timer_TIM4] = TIM4,
	[Timer_TIM5] = TIM5,
};

static uint32_t const TIMER_CLOCK_ENS[] =
{
	[Timer_TIM2] = RCC_APB1ENR_TIM2EN,
	[Timer_TIM3] = RCC_APB1ENR_TIM3EN,
	[Timer_TIM4] = RCC_APB1ENR_TIM4EN,
	[Timer_TIM5] = RCC_APB1ENR_TIM5EN,
};


void pwmInit(Timer_e timer, Tim_Channel_e chan, float initialDuty)
{
//	// Configure GPIO D15
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable GPIOD clock
	MODIFY_REG(GPIOD->MODER, GPIO_MODER_MODER15, (0x02 << GPIO_MODER_MODER15_Pos));  // alternative function mode
	MODIFY_REG(GPIOD->AFR[1], GPIO_AFRH_AFSEL15, AF2 << GPIO_AFRH_AFSEL15_Pos); // blue LED connected to timer4 channel4 on af2
	
	TIM_TypeDef* TIMx = TIMERS[timer];
	uint32_t RCC_APB1ENR_TIMxEN = TIMER_CLOCK_ENS[timer];  // assume all clocks passed in 
	uint32_t OCM_PWM = 0x6;
	// use APB1 for now.
	
	// Configure timer 4- it's the only timer for pin D15
	RCC->APB1ENR |= RCC_APB1ENR_TIMxEN;  // enable timer clock
	TIMx->ARR = GET_ARR_VALUE();
	TIMx->CCR4 = (TIMx->ARR * initialDuty);
	
	// mode: 
	// What varies: CCMRx register
	if (chan == Timer_Chan1 || chan == Timer_Chan2)
	{
	}
	else
	{
		TIMx->CCMR2 &= ~TIM_CCMR2_CC4S;  // CC4S: compare capture chan 4 is output
		MODIFY_REG(TIMx->CCMR2, TIM_CCMR2_OC4M, (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)); // PWM mode 1, channel active as long as CNT < CCR1 (in upcount)
		TIMx->CCMR2 |= TIM_CCMR2_OC4CE;  // enable output compare 4
	}

	TIMx->CCER |= TIM_CCER_CC4E; // capture compare output enable - do we need this?
	
	TIMx->CR1 |= (TIM_CR1_CEN);  // enable timer
}

void updateDuty(int value)
{
	
}
