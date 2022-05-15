#include "MyLed.h"
#include "io_handler.h"
#include "io_mapping_v1.h"
#include "MyPWM.h"

static int ledsInitialised = 0;  // will remain 1 once initialised

typedef enum GPIO_STATE_e LED_STATE_e;

const float LED_ON = 1.0;
const float LED_OFF = 0.0;

// Initialise all LEDs on the board
void initLEDs(void)
{
	// enable clock, assuming all LEDs are on port D
	rcc_enable_gpio_port_clock(GPIO_PORT_D);
	// set up the LED parameters
	GPIO_type myLed;
	myLed.mode = GPIO_MODE_AF;
	myLed.port = LED_PORT;
	myLed.pin = LED_GREEN_PIN;
	myLed.AFValue = LED_GREEN_TIM_AF;
	// green LED
	gpio_init(myLed);		// init green gpio
	pwmInit(LED_GREEN_TIM, LED_GREEN_TIM_CHANNEL, LED_ON); // init GREEN led PWM
	// orange LED
	myLed.pin = LED_ORANGE_PIN;
	myLed.AFValue = LED_ORANGE_AF;
	gpio_init(myLed);  // init orange
	pwmInit(LED_ORANGE_TIM, LED_ORANGE_TIM_CHANNEL, LED_ON); // init ORANGE led PWM
	// red LED
	myLed.pin = LED_RED_PIN;
	myLed.AFValue = LED_RED_AF;
	gpio_init(myLed);  // init red
	pwmInit(LED_RED_TIM, LED_RED_TIM_CHANNEL, LED_ON); // init RED led PWM
	// blue LED
	myLed.pin = LED_BLUE_PIN;
	myLed.AFValue = LED_BLUE_AF;
	gpio_init(myLed);  // init blue
	pwmInit(LED_BLUE_TIM, LED_BLUE_TIM_CHANNEL, 0.05); // init BLUE led PWM
	ledsInitialised = 1;
}

// Set the state of the LEDs
// led is a bitmask for the LEDs
static void enableLEDs(float newDutyRatio, LEDs_e led)
{
	// only do so if LEDs initialised
	if (ledsInitialised)
	{
		// dis/enable any of the LEDs passed in
		if (led & LED_RED)
		{
			updateDutyRatio(LED_RED_TIM, LED_RED_TIM_CHANNEL, newDutyRatio);
		}
		if (led & LED_ORANGE)
		{
			updateDutyRatio(LED_ORANGE_TIM, LED_ORANGE_TIM_CHANNEL, newDutyRatio);
		}
		if (led & LED_BLUE)
		{
			updateDutyRatio(LED_BLUE_TIM, LED_BLUE_TIM_CHANNEL, newDutyRatio);
		}
		if (led & LED_GREEN)
		{
			updateDutyRatio(LED_GREEN_TIM, LED_GREEN_TIM_CHANNEL, newDutyRatio);
		}
	}
}


// Turn on LEDs if initialised
void turnOnLED(LEDs_e led)
{
	// only do so if LEDs initialised
	if (ledsInitialised)
	{
		// dis/enable any of the LEDs passed in
		if (led & LED_RED)
		{
			channelOutputOn(LED_RED_TIM, LED_RED_TIM_CHANNEL);
		}
		if (led & LED_ORANGE)
		{
			channelOutputOn(LED_ORANGE_TIM, LED_ORANGE_TIM_CHANNEL);
		}
		if (led & LED_BLUE)
		{
			channelOutputOn(LED_BLUE_TIM, LED_BLUE_TIM_CHANNEL);
		}
		if (led & LED_GREEN)
		{
			channelOutputOn(LED_GREEN_TIM, LED_GREEN_TIM_CHANNEL);
		}
	}
}

// Turn off LEDs if initialised
void turnOffLED(LEDs_e led)
{
		// only do so if LEDs initialised
	if (ledsInitialised)
	{
		// dis/enable any of the LEDs passed in
		if (led & LED_RED)
		{
			channelOutputOff(LED_RED_TIM, LED_RED_TIM_CHANNEL);
		}
		if (led & LED_ORANGE)
		{
			channelOutputOff(LED_ORANGE_TIM, LED_ORANGE_TIM_CHANNEL);
		}
		if (led & LED_BLUE)
		{
			channelOutputOff(LED_BLUE_TIM, LED_BLUE_TIM_CHANNEL);
		}
		if (led & LED_GREEN)
		{
			channelOutputOff(LED_GREEN_TIM, LED_GREEN_TIM_CHANNEL);
		}
	}
}

void LEDSelectBrightness(LEDs_e led, float dutyRatio)
{
	enableLEDs(dutyRatio, led);
}

// toggle selected LEDs
void toggleLED(LEDs_e led) // TODO for PWM
{
	if (ledsInitialised)
	{
		// dis/enable any of the LEDs passed in
		if (led & LED_RED)
		{
			channelOutputToggle(LED_RED_TIM, LED_RED_TIM_CHANNEL);
		}
		if (led & LED_ORANGE)
		{
			channelOutputToggle(LED_ORANGE_TIM, LED_ORANGE_TIM_CHANNEL);
		}
		if (led & LED_BLUE)
		{
			channelOutputToggle(LED_BLUE_TIM, LED_BLUE_TIM_CHANNEL);
		}
		if (led & LED_GREEN)
		{
			channelOutputToggle(LED_GREEN_TIM, LED_GREEN_TIM_CHANNEL);
		}
	}
}

