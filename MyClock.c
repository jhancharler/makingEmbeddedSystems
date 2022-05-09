#include <stm32f407xx.h>
#include "MyClock.h"

static volatile ticks_t sysemTicks = 0;

void initSystemClock(void)
{
		SysTick_Config(SystemCoreClock / 1000);  // tick every ms
}

ticks_t sysClock(void)
{
	return sysemTicks;
}

void SysTick_Handler(void)
{
	sysemTicks++;
}
