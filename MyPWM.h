#ifndef MY_PWM_INCLUDED_H
#define MY_PWM_INCLUDED_H

#include "io_pin_definitions.h"

// What varies:
// Timer (TIMx) x= 2-5 for now
// Channel 1-4
// Initial fq perhaps this can be a compiler switch only
// Initial duty 0 to 1 indicating pct

void pwmInit(Timer_e timer, Tim_Channel_e chan, float initialDuty);
void updateDutyRatio(Timer_e timer, Tim_Channel_e chan, float newDuty);
void channelOutputOff(Timer_e TIMx, Tim_Channel_e channel);
void channelOutputOn(Timer_e TIMx, Tim_Channel_e channel);
void channelOutputToggle(Timer_e timer, Tim_Channel_e channel);

#endif
