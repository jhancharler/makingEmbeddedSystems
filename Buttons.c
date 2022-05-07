#include "Buttons.h"
#include "MyGpio.h"
#include "MyRCC.h"

void initButtons(void)
{
	ENABLE_BTN_CLOCK();
	initGPIO(BTN_PORT, BTN_USR1, GPIO_MODE_INPUT);
}

ButtonState_e readButton(BTNS_e btnPin)
{
	return readGPIO(BTN_PORT, btnPin);
}
