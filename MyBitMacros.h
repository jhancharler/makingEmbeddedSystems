#ifndef MY_BIT_MACROS_INCLUDED
#define MY_BIT_MACROS_INCLUDED

// Set bit
#define SET_BIT(reg, bit) ((reg) |= (1UL << (bit)))
// Clear bit
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1UL << bit))
// Read bit
#define READ_BIT(reg, bit)	(((reg) >> (bit)) & 0x1UL)
// Toggle bit
#define TOGGLE_BIT(reg, bit) ((reg) ^= (0x1UL << (bit)))

// Set reg
#define SET_REG(reg, val) ((reg) = (val))
// Clear reg
#define CLEAR_REG(reg)    ((reg = 0))
// Read reg
#define READ_REG(reg)			(reg)
// Modify reg
#define MODIFY_REG(reg, mask, value) ((reg) &= ~(mask)); ((reg) |= (value))

#endif
