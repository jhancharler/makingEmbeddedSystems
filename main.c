#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"

#include "io_mapping_v1.h"
#include "MyClock.h"

#include "MyPWM.h"

unsigned volatile int buttonCounter = 0;
const ticks_t debounceTime = 20; // ms
LEDs_e ledToToggle = LED_BLUE;  // state variable showing which LED to toggle
clockFrequency_e clockFq = CLOCK_FQ_8;
uint8_t updatePending = 0;

// todo: try doing static_assert to check size of float/double
int main(void)
{
	initLEDs();
	initButtons();
	initSystemClock(clockFq);
	
	enableGpioIRQ(BTN_USR_PORT, BTN_USR_PIN, IRQ_FALLING);
	turnOnLED(LED_ORANGE);

	ticks_t timeNow = sysClock();
	float org_ledBrightness = 0.85f;
	int ledOrgDirection = 1;
	float increment = 0.00001f;
	while (1)
	{
		LEDSelectBrightness(LED_ORANGE, org_ledBrightness);
		
		ledOrgDirection = (org_ledBrightness >= 1.0f) ? (turnOnLED(LED_BLUE), -1) : ledOrgDirection;
		ledOrgDirection = (org_ledBrightness <= 0.0f) ? (turnOffLED(LED_BLUE), 1) : ledOrgDirection;
		
		org_ledBrightness += (ledOrgDirection * increment);
	}
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	toggleLED(ledToToggle);
	clearUpdate();
}

void EXTI0_IRQHandler(void)
{
	clearPendingInterrupt(BTN_USR_PIN);
	static ticks_t lastIRQ = 0; 
	if (sysClock() - lastIRQ > debounceTime)
	{
		clockFq = (clockFq == CLOCK_FQ_LAST) ? CLOCK_FQ_FIRST + CLOCK_FQ_FIRST : clockFq + CLOCK_FQ_FIRST;
		toggleLED(LED_GREEN);
		updatePending = 1;
	}
	lastIRQ = sysClock();
}


