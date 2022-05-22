// Create a struct which contains details for Task
// Task has a runNextAt, timeBetweenRuns and the callback.
// Let the callback be something we decide in a second...

// TODO 0: Write a program for pelican crossing
// There are two routined: go and stop.
// Stop routine is green -> amber -> red | green 10s, amber 2 secs, red 10s.
// Go routine is red -> amber (flash) -> green 10s | amber 2 sec flash every 0.5s | red 10s
// When light is green, and a button is pressed, the Go routine is called after at most 2 seconds
// Implement this using a scheduler


#include "MyClock.h"
#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"

#define SCHEDULER_PERIOD	250
int isButtonPressed = 0;

typedef struct Task Task;
typedef void (*CallbackFunctionPtr)(Task*);
typedef struct Task
{
	ticks_t runNextAt;
	ticks_t period;
	CallbackFunctionPtr func;
	int state;
} Task;

typedef enum
{
	STATE_AMBER_FLASH,
	STATE_AMBER_SOLID,
	STATE_RED_SOLID,
	STATE_GREEN_SOLID,
} GoState_e;

typedef enum Tasks_e
{
	TASK_GREENLED,
	TASK_ORANGELED,
	TOTAL_TASK
} Tasks_e;

void toggleGreenLed(void);
void toggleOrgLed(void);
void nextState(Task* task);

// todo: function pointers & scheduler
// todo: try doing static_assert to check size of float/double
int main(void)
{
	initPeriodicSystemClocks(); // init systick, 1ms tick
	initLEDs();
	initButtons();
	Task tasks[TOTAL_TASK];
	
	tasks[TASK_GREENLED].period = 500; // every 500 ms
	tasks[TASK_GREENLED].runNextAt = 250;
	tasks[TASK_GREENLED].func = &nextState;
	tasks[TASK_GREENLED].state = STATE_RED_SOLID;
	
	ticks_t schedulerTime = sysClock();
	while(1)
	{
		// scheduler
		if (timeSince(schedulerTime) >= SCHEDULER_PERIOD)
		{
			schedulerTime = sysClock();
			// run scheduler; go through each of its tasks
			for (int i = 0; i < TOTAL_TASK; i++)
			{
				if (tasks[i].runNextAt <= schedulerTime) // task ready
				{
					(tasks[i].func)(&tasks[i]);	// execute task
				}
				// housekeeping
				if (tasks[i].state != STATE_AMBER_SOLID)
				{
					isButtonPressed = 0; // ignore button press if button was pressed on other states
				}
				if (tasks[i].state == STATE_AMBER_SOLID && isButtonPressed == 1)
				{
					if (schedulerTime + 1000 < tasks[i].runNextAt)  // pedestrian pressed button, go green after 1 sec at most
					{
						tasks[i].runNextAt = schedulerTime + 1000;
					}
					isButtonPressed = 0;
				}

			}
		}
		// do other things
		volatile int ab = 10;
	}

}

void nextState(Task* task)
{
	switch (task->state)
	{
		case STATE_AMBER_FLASH:  // amber flashing state
		{
			int maxToggle = 2000 / 250;
			static int counter = 0;
			turnOffLED(LED_RED);
			toggleLED(LED_ORANGE);
			task->period = 250; //
			if (counter >= maxToggle)
			{
				// enough toggles
				task->state = STATE_GREEN_SOLID;
				turnOffLED(LED_ORANGE);
				counter = 0;
			}
			counter++;
			
		}
		break;
		case STATE_GREEN_SOLID:  // green light state
		{
			// next state after amber is green light
			turnOffLED(LED_ORANGE);
			turnOnLED(LED_GREEN);
			task->state = STATE_AMBER_SOLID;
			task->period = 5000; // ms
		}
		break;
		case STATE_AMBER_SOLID:  // amber solid state
		{
			turnOffLED(LED_GREEN);
			turnOnLED(LED_ORANGE);
			task->state = STATE_RED_SOLID;
			task->period = 2000; // ms
		}
		break;
		case STATE_RED_SOLID:  // red solid state
		{
			turnOffLED(LED_ORANGE);
			turnOffLED(LED_GREEN);
			turnOnLED(LED_RED);
			task->state = STATE_AMBER_FLASH;
			task->period = 5000; // ms
		}
		break;
		default:
		{
			// shouldn't come here
		}
		break;
	};
	task->runNextAt += task->period;
}

void toggleGreenLed(void)
{
	toggleLED(LED_GREEN);
}

void toggleOrgLed(void)
{
	toggleLED(LED_ORANGE);
}

void EXTI0_IRQHandler(void)
{
	clearPendingInterrupt(GPIO_PIN_0);
	isButtonPressed = 1;
}


void TIM1_UP_TIM10_IRQHandler(void)
{
	toggleLED(LED_BLUE);
	clearUpdate();
}
