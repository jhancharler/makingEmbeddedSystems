// Create a struct which contains details for Task
// Task has a runNextAt, timeBetweenRuns and the callback.
// Let the callback be something we decide in a second...

// TODO 0: Write a program for pelican crossing
// There are two routines: go and stop.
// Stop routine is green -> amber -> red | green 10s, amber 2 secs, red 10s.
// Go routine is red -> amber (flash) -> green 10s | amber 2 sec flash every 0.5s | red 10s
// When light is green, and a button is pressed, the Go routine is called after at most 2 seconds
// Implement this using a scheduler


#include "MyClock.h"
#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"
#include "MySPI.h"
#include "MyLIS3DSH.h"

#define SCHEDULER_PERIOD	250
int isButtonPressed = 0;

int main(void)
{
	initLEDs();
	initButtons();
	initPeriodicSystemClocks();

	accel_lis3dsh_init();
	
	AccelData myData = { 0 };
	
	while(1)
	{
		if (isButtonPressed)
		{
			accel_lis3dsh_read_data(&myData);
			isButtonPressed = 0;
		}
	}
}


void EXTI0_IRQHandler(void)
{
	clearPendingInterrupt(GPIO_PIN_0);
	isButtonPressed = 1;
	toggleLED(LED_GREEN);
}


void TIM1_UP_TIM10_IRQHandler(void)
{
	toggleLED(LED_BLUE);
	clearUpdate();
}
