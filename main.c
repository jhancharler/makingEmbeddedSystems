#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"

#include "io_mapping_v1.h"
#include "MyClock.h"

unsigned volatile int buttonCounter = 0;
const ticks_t debounceTime = 20; // ms
LEDs_e ledToToggle = LED_BLUE;  // state variable showing which LED to toggle

int main(void)
{
	initLEDs();
	initButtons();
	initSystemClock();
	
	enableGpioIRQ(BTN_USR_PORT, BTN_USR_PIN, IRQ_FALLING);
	turnOnLED(LED_ORANGE);
	
	ticks_t lastTimeLedWasToggled = 0;
	ticks_t timeNow;

	while (1)
	{
		timeNow = sysClock();
		if (sysClock() > (lastTimeLedWasToggled + 500))
		{
			toggleLED(ledToToggle);
			lastTimeLedWasToggled = timeNow;
		}
	}
}

void EXTI0_IRQHandler(void)
{
	clearPendingInterrupt(BTN_USR_PIN);
	static ticks_t lastIRQ = 0; 
	if (sysClock() - lastIRQ > debounceTime)
	{
		ledToToggle = (ledToToggle == LED_RED) ? LED_GREEN : (LEDs_e)(ledToToggle >> 1);
	}
	lastIRQ = sysClock();
}


