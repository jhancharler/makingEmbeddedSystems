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


typedef enum
{
	CCxS_Mask = 0x3UL,
	OCxFE_Mask = 0x4UL,
	OCxPE_Mask = 0x8UL,
	OCxM_Mask = 0x70UL,
	OCxE_Mask = 0x80UL
} CCMRx_Masks_e;


void pwmInit(Timer_e timer, Tim_Channel_e chan, float initialDuty)
{
	// Parse input parameters
	TIM_TypeDef* TIMx = TIMERS[timer];
	uint32_t RCC_APB1ENR_TIMxEN = TIMER_CLOCK_ENS[timer];
	uint32_t OCM_PWM = 0x6UL << 4;
	__IO uint32_t* CCMRxRegister;  // capture reload mode reg
	uint8_t bitShiftForCCMRx;  // position in reload mode register
	__IO uint32_t* CCRxRegister;  // capture reload reg
	if (chan == Timer_Chan_2 || chan == Timer_Chan_4)
	{
		bitShiftForCCMRx = 8;
		CCMRxRegister = &TIMx->CCMR2;
	}
	
	// configure timer
	RCC->APB1ENR |= RCC_APB1ENR_TIMxEN;  // enable timer clock (just use APB1 for now).
	TIMx->ARR = GET_ARR_VALUE();	// set up frequency for this timer
	switch (chan)	// set up duty ratio for this channel
	{
		case Timer_Chan_1:
		{
			CCRxRegister = &TIMx->CCR1; 
			CCMRxRegister = &TIMx->CCMR1;  
			bitShiftForCCMRx = 0;  
		}
		break;
		case Timer_Chan_2:
		{
			CCRxRegister = &TIMx->CCR2;
			CCMRxRegister = &TIMx->CCMR1;
			bitShiftForCCMRx = 8; 
		}
		break;
		case Timer_Chan_3:
		{
			CCRxRegister = &TIMx->CCR3;
			CCMRxRegister = &TIMx->CCMR2;
			bitShiftForCCMRx = 0;
		}
		break;
		case Timer_Chan_4:
		{
			CCRxRegister = &TIMx->CCR4;
			CCMRxRegister = &TIMx->CCMR2;
			bitShiftForCCMRx = 8;
		}
		break;
	}
	*CCRxRegister = (TIMx->ARR * initialDuty);
	
	// configure this channel
	*CCMRxRegister &= ~(CCxS_Mask << bitShiftForCCMRx);  	// capture channel is output
	MODIFY_REG(*CCMRxRegister, (OCxM_Mask << bitShiftForCCMRx), (OCM_PWM << bitShiftForCCMRx)); // channel is PWM mode 1
	*CCMRxRegister |= (OCxE_Mask << bitShiftForCCMRx);  // enable output on capture channel
	TIMx->CR1 |= (TIM_CR1_CEN);  // enable TIMx timer
	TIMx->CCER |= (0x1UL << (chan * 4)); // enable capture output
}

void updateDutyRatio(Timer_e timer, Tim_Channel_e chan, float newDuty)
{
	TIM_TypeDef* TIMx = TIMERS[timer];	// get TIM struct handle
	uint32_t newCCR = GET_ARR_VALUE() * newDuty;	// calculate new value of CCR
	__IO uint32_t* CCRx = &(TIMx->CCR1) + chan;	// get CCR register
	*CCRx = newCCR;	// update CCR register
}

void channelOutputOn(Timer_e timer, Tim_Channel_e channel)
{
	TIM_TypeDef* TIMx = TIMERS[timer];	// get TIM struct handle
	TIMx->CCER |= (0x1UL << (channel * 4)); // enable capture output
}

void channelOutputOff(Timer_e timer, Tim_Channel_e channel)
{
	TIM_TypeDef* TIMx = TIMERS[timer];	// get TIM struct handle
	TIMx->CCER &= ~(0x1UL << (channel * 4)); // disable capture output
}

void channelOutputToggle(Timer_e timer, Tim_Channel_e channel)
{
	TIM_TypeDef* TIMx = TIMERS[timer];	// get TIM struct handle
	TIMx->CCER ^= (0x1UL << (channel * 4)); // disable capture output
}
