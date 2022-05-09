#ifndef MY_BIT_MACROS_H_INCLUDED
#define MY_BIT_MACROS_H_INCLUDED

#define MODIFY_REG(reg, mask, value)	((reg) &= ~(mask));(reg |= (value))

#endif
