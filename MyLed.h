#ifndef MY_LED_INCLUDED
#define MY_LED_INCLUDED

#define MAX_LEDS	4

typedef enum LEDs_e
{
	LED_RED = 0x01UL,
	LED_ORANGE = 0x02UL,
	LED_BLUE = 0x04UL,
	LED_GREEN = 0x08UL
} LEDs_e;

void initLEDs(void);
void turnOnLED(LEDs_e led);
void turnOffLED(LEDs_e led);
void toggleLED(LEDs_e led);
void LEDSelectBrightness(LEDs_e led, float dutyRatio);

#endif
