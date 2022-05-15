#ifndef MY_PWM_INCLUDED_H
#define MY_PWM_INCLUDED_H

// What varies:
// Timer (TIMx) x= 2-5 for now
// Channel 1-4
// Initial fq perhaps this can be a compiler switch only
// Initial duty 0 to 1 indicating pct

typedef enum
{
	Timer_TIM2,
	Timer_TIM3,
	Timer_TIM4,
	Timer_TIM5
} Timer_e;

typedef enum
{
	Timer_Chan1,
	Timer_Chan2,
	Timer_Chan3,
	Timer_Chan4
} Tim_Channel_e;


void pwmInit(Timer_e timer, Tim_Channel_e chan, float initialDuty);

void updateDuty(int value);

#endif
