#ifndef MY_CLOCK_INCLUDED
#define MY_CLOCK_INCLUDED

#include <stdint.h>

typedef uint64_t ticks_t;

typedef enum
{
	CLOCK_FQ_13,
	CLOCK_FQ_17
} clockFrequency_e;

void initSystemClock(clockFrequency_e frequency);
uint8_t updateHappened(void);
void clearUpdate(void);
ticks_t sysClock(void);

#endif
