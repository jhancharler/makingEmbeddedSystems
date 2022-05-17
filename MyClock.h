#ifndef MY_CLOCK_INCLUDED
#define MY_CLOCK_INCLUDED

#include <stdint.h>

typedef uint64_t ticks_t;

typedef enum
{
	CLOCK_FQ_FIRST = 1,
	CLOCK_FQ_8,
	CLOCK_FQ_13,
	CLOCK_FQ_17,
	CLOCK_FQ_LAST,
} clockFrequency_e;

void initPeriodicSystemClocks(void);
void startTimer2(void);
void clearUpdateTim2(void);
uint8_t updateHappened(void);
void clearUpdate(void);
ticks_t sysClock(void);

void delayMs(ticks_t ms);
ticks_t timeSince(ticks_t then);

#endif
