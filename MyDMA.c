#include <stm32f407xx.h>
#include "MyDMA.h"
#include "MyBitMacros.h"

// [x] TODO : write driver to copy memory to memory
    // I want the DMA to make a copy of some data I have in the background
// [x] TODO 2: make driver more generic
// [] TODO 3: play around with different settings; try FIFO?
// [] TODO 4: Transfer SPI data from accelerometer to buffer. Interrupt so we know it happened

static IRQn_Type streamToIrq(DMA_Stream_TypeDef* dma_stream);

/*
 * @brief Initialises DMA controller
 * 
 * @detail Uses stream 0 channel 0 for the time being only
 * 
 * @param DMAInit_s dma_init - The initialisation struct for DMA
 * 
*/
void dma_init(const DMAInit_s* init_s)
{
    DMA_Stream_TypeDef* DmaStream = init_s->dmaStream;
    
    MODIFY_REG(DMA2_Stream0->CR, DMA_SxCR_EN, 0);   // disable stream
    while(DMA2_Stream0->CR & DMA_SxCR_EN);	// wait until it finishes

	// enable periph clock
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	// which channel to use
	MODIFY_REG(DmaStream->CR, DMA_SxCR_CHSEL_Msk, init_s->channel);	// let's use channel 0, stream 0
	// size of data xfer
	MODIFY_REG(DmaStream->CR, DMA_SxCR_MSIZE_Msk, init_s->msize);
	// direction config
	MODIFY_REG(DmaStream->CR, DMA_SxCR_DIR_Msk, init_s->direction);
	// memory increment config. here, DMA is the flow controller, but source is actually periph register!
	MODIFY_REG(DmaStream->CR, DMA_SxCR_MINC_Msk, init_s->memoryInc);
    // periph increment config
	MODIFY_REG(DmaStream->CR, DMA_SxCR_PINC_Msk, init_s->periphInc);
    // Configure circular buffer
    MODIFY_REG(DmaStream->CR, DMA_SxCR_CIRC_Msk ,init_s->circularDma);
    // data size
    MODIFY_REG(DmaStream->CR, DMA_SxCR_PSIZE_Msk, init_s->psize);
	// interrupts
	MODIFY_REG(DmaStream->CR, DMA_SxCR_TCIE_Msk, init_s->completeIrq);  // enable transfer complete interrupt! TODO
	// config data size
	MY_SET_REG(DmaStream->NDTR, init_s->bufferSize); // 0 up to 65535 (0xFFFF)
    // periph/mem ptr config
    MY_SET_REG(DmaStream->PAR, init_s->periphBaseAddress);
    MY_SET_REG(DmaStream->M0AR, init_s->memoryBaseAddress);
    
    // interrupts
    if (init_s->completeIrq & TransferCompleteInterrupt_en)
    {
        NVIC_EnableIRQ(streamToIrq(DmaStream));
    }
}

void dma_enablexfer(void)
{
	// enable transfer
	DMA2_Stream0->CR |= DMA_SxCR_EN;	// begin!
}


static IRQn_Type streamToIrq(DMA_Stream_TypeDef* dma_stream_ptr)
{
    IRQn_Type type;
    uint32_t dma_stream = (uint32_t)dma_stream_ptr; // WARNING: assumes 32 bit address
    switch (dma_stream)
    {
        case ((uint32_t)DMA1_Stream0):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream0_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream1):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream1_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream2):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream2_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream3):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream3_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream4):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream4_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream5):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream5_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream6):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream6_IRQn;
        } 
        break;
        case ((uint32_t)DMA1_Stream7):  // WARNING: assumes 32 bit address
        {
            type = DMA1_Stream7_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream0):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream0_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream1):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream1_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream2):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream2_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream3):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream3_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream4):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream4_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream5):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream5_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream6):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream6_IRQn;
        } 
        break;
        case ((uint32_t)DMA2_Stream7):  // WARNING: assumes 32 bit address
        {
            type = DMA2_Stream7_IRQn;
        } 
        break;
        default:
        {
            // shouldn't come
        }
        break;
    }
    return type;
}

/*
 * @brief   Interrupt for DMA2 stream 3
 * @details Use this to clear the flags so DMA can be enabled again.
*/
void DMA2_Stream0_IRQHandler(void)
{
    // clear interrupts
    MODIFY_REG(DMA2->LIFCR, DMA_LIFCR_CTCIF0_Msk, DMA_LIFCR_CTCIF0);
    MODIFY_REG(DMA2->LIFCR, DMA_LIFCR_CHTIF0_Msk, DMA_LIFCR_CHTIF0);
    dma_enablexfer();
}