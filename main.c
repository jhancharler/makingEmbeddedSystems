// Create a struct which contains details for Task
// Task has a runNextAt, timeBetweenRuns and the callback.
// Let the callback be something we decide in a second...

// TODO 0: Write a program for pelican crossing
// There are two routines: go and stop.
// Stop routine is green -> amber -> red | green 10s, amber 2 secs, red 10s.
// Go routine is red -> amber (flash) -> green 10s | amber 2 sec flash every 0.5s | red 10s
// When light is green, and a button is pressed, the Go routine is called after at most 2 seconds
// Implement this using a scheduler


#include "MyClock.h"
#include "MyLed.h"
#include "MyButton.h"
#include "MyEXTI.h"
#include "MySPI.h"
#include "MyLIS3DSH.h"
#include "MyDMA.h"

#define SCHEDULER_PERIOD	250
int isButtonPressed = 0;

#define SIZE_OF_ARR(arr)    (sizeof((arr)) / sizeof((arr)[0]))

uint32_t myRandomFrom[] = { 13232, 211, 3233, 4544, 5667, 677, 7764, 832, 977, 127433 };
uint8_t myRandomTo[SIZE_OF_ARR(myRandomFrom)] = { 0 };

int main(void)
{
	DMAInit_s dmaStruct;
	
	initLEDs();
	initButtons();
	initPeriodicSystemClocks();

	accel_lis3dsh_init();
	
    #if (0)
	AccelData myData = { 0 };
	#endif
    
    // Settings for SPI1 rcceive
    dmaStruct.dmaStream = DMA2_Stream0; // DMA2 stream 0 (dma2 is the only one that can do m2m)
	dmaStruct.bufferSize =  sizeof(myRandomTo);
	dmaStruct.direction = DMA_DIR_PER2MEM_e;
	dmaStruct.memoryInc = MemoryInc_En;
	dmaStruct.periphInc = PeriphInc_Dis;    
	dmaStruct.memoryBaseAddress = (uint32_t)myRandomTo;	// WARNING: assumes 32 bit addr
	dmaStruct.periphBaseAddress = getSPI1RxReg();;	// mem2mem from addr is periph addr
    dmaStruct.channel = DMA_CHSEL_CHANNEL_3;    // channel doesn't matter for mem2mem, but does for periphs. SPI1 receive is CH3, STR0
    dmaStruct.msize = DMA_MSIZE_BYTE; // size of each transfer for memory
    dmaStruct.psize = DMA_PSIZE_BYTE; // size of each transfer for memory
    dmaStruct.completeIrq = TransferCompleteInterrupt_en;
    dmaStruct.flowControl = FLOWCONTROL_DMA;    // DMA is flow control meaning the counter determines size;
    dmaStruct.circularDma = CIRCULAR_DMA_en;    // enable so we wrap round when done
	dma_init(&dmaStruct);
    dma_enablexfer();   // enable xfer, will not xfer till receive requested by SPI
	
	while(1)
	{
		if (isButtonPressed)
		{
			//accel_lis3dsh_read_data(&myData);
            accel_lis3dsh_read_data_DMA(10);    // read 10 bytes
			isButtonPressed = 0;
		}
	}
}


void EXTI0_IRQHandler(void)
{
	clearPendingInterrupt(GPIO_PIN_0);
	isButtonPressed = 1;
	toggleLED(LED_GREEN);
}


void TIM1_UP_TIM10_IRQHandler(void)
{
	toggleLED(LED_BLUE);
	clearUpdate();
}

