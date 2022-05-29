#include "MyWatchdog.h"
#include "stm32f407xx.h"

enum
{
	IWDG_KR_START_WDG = 0xCCCC,
	IWDG_KR_SERVICE_WDG = 0xAAAA,
	IWDG_KR_EN_WRITE_WDG = 0x5555,
};

enum
{
	IWDG_PR_DIV4,
	IWDG_PR_DIV8,
	IWDG_PR_DIV16,
	IWDG_PR_DIV32,
	IWDG_PR_DIV64,
	IWDG_PR_DIV128,
	IWDG_PR_DIV256,
	IWDG_PR_DIV256_2,
};

void initWatchdog(void)
{
	// IWDG_KR = 0xCCCC | starts watchdog to count down from 0xFFF to 0, IWDG Reset signal generated
	// IWDG_KR = 0xAAAA | IWDG_RLR value is reloaded, so watchdog is services and won't generate reset
	// IWDG_KR = 0x5555 | This removes write access to IWDG_PR and IWDG_RLR registers. Write anything else to disable write access again.
	
	// DBG_IWDG_STOP configures if debugging should stop watchdog, in the DBG module
	
	// To init:
	// Enable write access with 0x5555
	IWDG->KR = IWDG_KR_EN_WRITE_WDG;
	// Set up prescaler and reload register
	IWDG->PR  = IWDG_PR_DIV256;  // maybe so it triggers after 2 secs?
	IWDG->RLR = 250;
	IWDG->KR = IWDG_KR_SERVICE_WDG; // reload value
	IWDG->KR = IWDG_KR_START_WDG; // start watchdog counter
}

void walkTheDog(void)
{
	IWDG->KR = IWDG_KR_SERVICE_WDG; // reload value
}
