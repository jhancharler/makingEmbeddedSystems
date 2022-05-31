#ifndef MY_BIT_MACROS_H_INCLUDED
#define MY_BIT_MACROS_H_INCLUDED

#define MODIFY_REG(reg, mask, value)	((reg) &= ~(mask));(reg |= (value))
#define MY_CLEAR_BIT(reg, pos)	((reg) &= ~(1UL << (pos)))
#define MY_SET_BIT(reg, pos) ((reg) |= (1UL << (pos)))

#endif
