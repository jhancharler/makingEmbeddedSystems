#include "MyButton.h"
#include "io_mapping_v1.h"
#include "io_handler.h"

//typedef enum Buttons_e
//{
//	BUTTON_USR
//} Buttons_e;

const GPIO_STATE_e buttonPressed = GPIO_STATE_HIGH;
const GPIO_STATE_e buttonReleased = GPIO_STATE_LOW;

void initButtons(void)
{
	// enable button port
	rcc_enable_gpio_port_clock(BTN_USR_PORT);
	
	GPIO_type usrButton = 
	{
		.pin = BTN_USR_PIN,
		.port = BTN_USR_PORT,
		.mode = GPIO_MODE_INPUT,
		.pupdown = GPIO_PUPD_NONE
	};
	gpio_init(usrButton);
	
	// initialise interrupt for button
	// TODO
}

// 1 if pressed,  0 if released
int buttonIsPressed(Buttons_e btn)
{
	return gpio_read(BTN_USR_PORT, BTN_USR_PIN) == buttonPressed;
}
