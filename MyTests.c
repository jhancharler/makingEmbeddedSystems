#include <assert.h>

#include "MyGpio.h"
#include "MyBitMacros.h"

static void bm_test()
{
	// bits
	int myBit = 0x50;
	SET_BIT(myBit, 2);  // set
	assert(myBit == 0x54);
	int ans = READ_BIT(myBit, 4);  // read
	assert(ans == 0x1);
	CLEAR_BIT(myBit, 4);  // clear
	assert(myBit == 0x44);
	TOGGLE_BIT(myBit, 2);	// toggle
	assert(myBit == 0x40);
	TOGGLE_BIT(myBit, 2);
	assert(myBit == 0x44);
	
	// register
	int myReg = 0;
	SET_REG(myReg, 0xDEADBEEF);
	assert(myReg == 0xDEADBEEF);
	CLEAR_REG(myReg);
	assert(myReg == 0x0UL);
	SET_REG(myReg, 0xDEADBEEF);
	assert(READ_REG(myReg) == 0xDEADBEEF);
	MODIFY_REG(myReg, 0xF0, 0xA0); // change last 0xE to an 0xA
	assert(myReg == 0xDEADBEAF);
}

void run_tests()
{
	bm_test();
}
