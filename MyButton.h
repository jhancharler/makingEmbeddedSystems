#ifndef MY_BUTTON_H_INCLUDED
#define MY_BUTTON_H_INCLUDED

typedef enum Buttons_e
{
	BUTTON_USR
} Buttons_e;

void initButtons(void);
int buttonIsPressed(Buttons_e btn);

#endif
