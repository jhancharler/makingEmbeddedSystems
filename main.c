#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"

#include "io_mapping_v1.h"
#include "MyClock.h"

#include "MyPWM.h"

const ticks_t debounceTime = 20; // ms
volatile uint8_t updatePending = 0;

typedef enum
{
	State_RED,
	State_YELLOW,
	State_GREEN,
} State_e;

typedef enum
{
	Event_GO,
	Event_STOP,
	Event_TIMEOUT,
} Event_e;

volatile State_e mainState = State_RED;
volatile Event_e mainEvent = Event_STOP;

// forward declarations
void nextState(void);

// todo: try doing static_assert to check size of float/double
int main(void)
{
	__disable_irq();
	
	initLEDs();
	initButtons();
	initPeriodicSystemClocks();
	enableGpioIRQ(BTN_USR_PORT, BTN_USR_PIN, IRQ_FALLING);
	
	turnOffLED(LED_GREEN | LED_BLUE | LED_RED | LED_ORANGE);
	// init event changers (timers)
	// need 1 timer for switching between go/time-out events (periodic)
	// need 1 timer for switching from timeout to stop (single shot)
	
	__enable_irq();
	while (1)
	{
		// Main state machine
		switch (mainState)
		{
			case State_RED:
			{
				turnOnLED(LED_RED);
				if (mainEvent == Event_GO)
				{
					turnOffLED(LED_RED);
					turnOnLED(LED_GREEN);
					nextState();
				}
			}
			break;
			case State_YELLOW:
			{
				// if flag raised, go next state
				if (mainEvent == Event_STOP)
				{
					turnOffLED(LED_ORANGE);
					turnOffLED(LED_GREEN);
					turnOnLED(LED_RED);
					nextState();
				}
			}
			break;
			case State_GREEN:
			{
				if (mainEvent == Event_TIMEOUT)
				{
					turnOnLED(LED_ORANGE);
					startTimer2();
					nextState();
				}
			}
			break;
			default:
			{
				// error handling
				// todo, make error handling module
			}
			break;
		};
	}
}

void nextState(void)
{
	// Main state machine
		switch (mainState)
		{
			case State_RED:
			{
				mainState = State_GREEN;
			}
			break;
			case State_YELLOW:
			{
				mainState = State_RED;
			}
			break;
			case State_GREEN:
			{
				mainState = State_YELLOW;
			}
			break;
			default:
			{
				// error handling
				// todo, make error handling module
			}
			break;
		};
}

// Periodic timer, switches state from GO to TIMEOUT and repeat
void TIM1_UP_TIM10_IRQHandler(void)
{
		clearUpdate();
		mainEvent = (mainEvent == Event_GO) ? Event_TIMEOUT : Event_GO;
}

// One shot timer, changes state to Event_STOP
void TIM2_IRQHandler(void)
{
		clearUpdateTim2();
		mainEvent = Event_STOP;
}

void EXTI0_IRQHandler(void)
{
	clearPendingInterrupt(BTN_USR_PIN);
	static ticks_t lastIRQ = 0; 
	if (sysClock() - lastIRQ > debounceTime)
	{
		toggleLED(LED_GREEN);
		updatePending = 1;
	}
	lastIRQ = sysClock();
}


