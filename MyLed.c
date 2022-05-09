#include "MyLed.h"
#include "io_handler.h"
#include "io_mapping_v1.h"

static int ledsInitialised = 0;  // will remain 1 once initialised

typedef enum GPIO_STATE_e LED_STATE_e;

const LED_STATE_e LED_ON = GPIO_STATE_HIGH;
const LED_STATE_e LED_OFF = GPIO_STATE_LOW;

// Initialise all LEDs on the board
void initLEDs(void)
{
	// enable clock
	rcc_enable_gpio_port_clock(GPIO_PORT_D);
	
	GPIO_type myLed = {.mode = GPIO_MODE_OUTPUT, .port = LED_PORT};
	myLed.pin = LED_GREEN_PIN;
	gpio_init(myLed);		// init green
	myLed.pin = LED_ORANGE_PIN;
	gpio_init(myLed);  // init orange
	myLed.pin = LED_RED_PIN;
	gpio_init(myLed);  // init red
	myLed.pin = LED_BLUE_PIN;
	gpio_init(myLed);  // init blue
	
	ledsInitialised = 1;
}

// Set the state of the LEDs
// led is a bitmask for the LEDs
static void enableLEDs(LED_STATE_e newState, LEDs_e led)
{
	// only do so if LEDs initialised
	if (ledsInitialised)
	{
		// dis/enable any of the LEDs passed in
		if (led & LED_RED)
		{
			gpio_enable(newState, LED_PORT, LED_RED_PIN);
		}
		if (led & LED_ORANGE)
		{
			gpio_enable(newState, LED_PORT, LED_ORANGE_PIN);
		}
		if (led & LED_BLUE)
		{
			gpio_enable(newState, LED_PORT, LED_BLUE_PIN);
		}
		if (led & LED_GREEN)
		{
			gpio_enable(newState, LED_PORT, LED_GREEN_PIN);
		}
	}
}

// Turn on LEDs if initialised
void turnOnLED(LEDs_e led)
{
	enableLEDs(LED_ON, led);
}

// Turn off LEDs if initialised
void turnOffLED(LEDs_e led)
{
	enableLEDs(LED_OFF, led);
}

// toggle selected LEDs
void toggleLED(LEDs_e led)
{
	// only do so if LEDs initialised
	if (ledsInitialised)
	{
		// toggle any of the LEDs passed in
		if (led & LED_RED)
		{
			gpio_toggle(LED_PORT, LED_RED_PIN);
		}
		if (led & LED_ORANGE)
		{
			gpio_toggle(LED_PORT, LED_ORANGE_PIN);
		}
		if (led & LED_BLUE)
		{
			gpio_toggle(LED_PORT, LED_BLUE_PIN);
		}
		if (led & LED_GREEN)
		{
			gpio_toggle(LED_PORT, LED_GREEN_PIN);
		}
	}
}
