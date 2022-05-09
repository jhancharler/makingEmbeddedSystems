#ifndef MY_CLOCK_INCLUDED
#define MY_CLOCK_INCLUDED

#include <stdint.h>

typedef uint64_t ticks_t;

void initSystemClock(void);
ticks_t sysClock(void);

#endif
