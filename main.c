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
	SIZE_Event,
} Event_e;

volatile State_e mainState = State_RED;
volatile Event_e mainEvent = Event_STOP;

// Event table, define struct first
typedef struct
{
	State_e currentState;
	LEDs_e light;
	State_e doEventGo;
	State_e doEventStop;
	State_e doEventTimeout;
} StateMachine;

// The state machine table
StateMachine states[SIZE_Event] =
{
	// Index				 | State    			| LED 	 			| GO event   		| STOP event 		| TIMEOUT event
	[State_RED] 	 = {State_RED, 			LED_RED, 			State_GREEN, 		State_RED,  		State_RED},
	[State_GREEN]  = {State_GREEN, 		LED_GREEN, 		State_GREEN, 		State_YELLOW,  	State_GREEN},
	[State_YELLOW] = {State_YELLOW, 	LED_ORANGE, 	State_YELLOW, 	State_YELLOW,  	State_RED},
};

// Event handlers
void HandleEventGo(StateMachine* state);
void HandleEventStop(StateMachine* state);
void HandleEventTimeout(StateMachine* state);

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
	StateMachine currentState = states[State_RED];
	while (1)
	{
		switch (mainEvent)
		{
			case Event_GO:
			{
				HandleEventGo(&currentState);
			}
			break;
			case Event_STOP:
			{
				HandleEventStop(&currentState);
			}
			break;
			case Event_TIMEOUT:
			{
				HandleEventTimeout(&currentState);
			}
			break;
			default:
			{
			}
			break;
		};
	}
}

void HandleEventGo(StateMachine* currentState)
{
	turnOffLED(currentState->light);
	*currentState = states[currentState->doEventGo];
	turnOnLED(currentState->light);
}

void HandleEventStop(StateMachine* currentState)
{
	turnOffLED(currentState->light);
	*currentState = states[currentState->doEventStop];
	turnOnLED(currentState->light);
}

void HandleEventTimeout(StateMachine* currentState)
{
	turnOffLED(currentState->light);
	*currentState = states[currentState->doEventTimeout];
	turnOnLED(currentState->light);
}

// Periodic timer, switches state from GO to TIMEOUT and repeat
void TIM1_UP_TIM10_IRQHandler(void)
{
	__disable_irq();

	mainEvent = mainEvent == Event_GO ? Event_STOP: Event_GO;
	if (mainEvent == Event_STOP)
	{
		startTimer2();
	}

	clearUpdate();
	
	__enable_irq();
}

// One shot timer, changes state to Event_STOP
void TIM2_IRQHandler(void)
{
	__disable_irq();
		clearUpdateTim2();
		mainEvent = Event_TIMEOUT;
	__enable_irq();
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


