/*
1. Turning on the Blue LED (PD15) on the STM32F4.
2. Flashing BLUE LED (PD15) on the STM32F4.
3. Flashing all other LEDS (ORANGE = PD13, GREEN = PD12, RED = PD14, BLUE = PD15).
4. Preprocessor switch
5. Organise the file structure
6. Add button, when held down the LED shall not blink.
*/

// GPIO D is on AHB1 bus, from 0x4002 0C00 - 0x4002 0FFF
// RCC_AHB1ENR

#include "LEDS.h"
#include "Buttons.h"

// Compiler switches
// #define RUN_TESTS_FIRST

// Optional headers
#ifdef RUN_TESTS_FIRST
#include "MyTests.h"
#endif


// Program
void delay(unsigned int cycles);

int main(void)
{
#ifdef RUN_TESTS_FIRST
	run_tests();
#endif
	
	initLEDS();
	initButtons();
	
	enableLED(LED_ON, LED_BLUE);
	enableLED(LED_ON, LED_RED);
	
	while(1)
	{
		if (readButton(BTN_USR1) == BUTTON_PRESSED)  // toggle only if in some state
		{
			toggleLED(LED_GREEN);
			delay(250000);
		}
		else
		{
			enableLED(LED_ON, LED_GREEN);  // turn on LED
		}
	}
}

void delay(unsigned int cycles)
{
	while (--cycles);
}
