#include "MyBitMacros.h"
#include "MyGpio.h"
#include "MyRCC.h"
#include "LEDS.h"

// Initialises all board LEDs
void initLEDS(void)
{
		ENABLE_LED_CLOCK();
		initGPIO(LED_PORT, LED_GREEN, 	GPIO_MODE_OUTPUT);
		initGPIO(LED_PORT, LED_ORANGE, 	GPIO_MODE_OUTPUT);
		initGPIO(LED_PORT, LED_RED, 		GPIO_MODE_OUTPUT);
		initGPIO(LED_PORT, LED_BLUE, 		GPIO_MODE_OUTPUT);
}
	
void toggleLED(LEDS_e led)
{
	toggleGPIO(LED_PORT, (gpio_pins_e)led);
}

// Turn on or off LED
void enableLED(LEDState_e ledState, LEDS_e led)
{
	enableGPIO(LED_PORT, led, ledState);
}
