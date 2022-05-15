#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"

#include "io_mapping_v1.h"
#include "MyClock.h"

#include "MyPWM.h"

unsigned volatile int buttonCounter = 0;
const ticks_t debounceTime = 20; // ms
LEDs_e ledToToggle = LED_BLUE;  // state variable showing which LED to toggle
clockFrequency_e clockFq = CLOCK_FQ_17;
uint8_t updatePending = 0;

// todo: try doing static_assert to check size of float/double
int main(void)
{
	pwmInit(Timer_TIM4, Timer_Chan4, 0.01f);
	initLEDs();
	initButtons();
	initSystemClock(clockFq);
	
	enableGpioIRQ(BTN_USR_PORT, BTN_USR_PIN, IRQ_FALLING);
	turnOnLED(LED_ORANGE);
	
	ticks_t timeNow = sysClock();
	while (1)
	{
		if (sysClock() > (timeNow + 100))
		{
			toggleLED(LED_ORANGE);
			timeNow = sysClock();
		}
		if (updatePending)
		{
			initSystemClock(clockFq);
			updatePending = 0;
		}
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
		clockFq = (clockFq == CLOCK_FQ_17) ? CLOCK_FQ_13 : CLOCK_FQ_17;
		toggleLED(LED_GREEN);
		updatePending = 1;
	}
	lastIRQ = sysClock();
}


