#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#include "the_io_board.h"

void initButtons(void);
ButtonState_e readButton(BTNS_e button);

#endif
