#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

#include "the_io_board.h"

// Initialises all board LEDs
void initLEDS(void);

// Toggle LED
void toggleLED(LEDS_e led);
// Enable LED
void enableLED(LEDState_e ledState, LEDS_e led);

#endif
