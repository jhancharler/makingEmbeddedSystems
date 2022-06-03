#ifndef MY_DMA_INCLUDED
#define MY_DMA_INCLUDED

#include <stdint.h>
#include <stm32f407xx.h>

typedef enum
{
    TransferCompleteInterrupt_dis = 0x0U,
    TransferCompleteInterrupt_en = DMA_SxCR_TCIE
} DMA_TransferComplete_e;

typedef enum
{
    MemoryInc_Dis = 0x0U,
    MemoryInc_En = DMA_SxCR_MINC,
} MemoryInc_e;

typedef enum
{
    PeriphInc_Dis = 0x0U,
    PeriphInc_En = DMA_SxCR_PINC,
} PeriphInc_e;

typedef enum
{
    DMA_DIR_PER2MEM_e = 0x0U,
    DMA_DIR_MEM2PER_e = DMA_SxCR_DIR_0,
    DMA_DIR_MEM2MEM_e = DMA_SxCR_DIR_1,
} DMA_Dir_e;

typedef enum
{
    DMA_MSIZE_BYTE = 0x0U,
    DMA_MSIZE_HALF_WORD = DMA_SxCR_MSIZE_0,
    DMA_MSIZE_WORD = DMA_SxCR_MSIZE_1,
} DMA_MSIZE_e;

typedef enum
{
    DMA_PSIZE_BYTE = 0x0U,
    DMA_PSIZE_HALF_WORD = DMA_SxCR_PSIZE_0,
    DMA_PSIZE_WORD = DMA_SxCR_PSIZE_1,
} DMA_PSIZE_e;

typedef enum
{
    DMA_CHSEL_CHANNEL_0 = 0x0U,
    DMA_CHSEL_CHANNEL_1 = DMA_SxCR_CHSEL_0,
    DMA_CHSEL_CHANNEL_2 = DMA_SxCR_CHSEL_1,
    DMA_CHSEL_CHANNEL_3 = (DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0),
} DMA_ChannelSelect_e;

typedef enum
{
    FLOWCONTROL_DMA = 0x0U,
    FLOWCONTROL_PERIPH = DMA_SxCR_PFCTRL,
} DMA_FLOWCONTROL_e;

typedef enum
{
    CIRCULAR_DMA_dis = 0x0U,
    CIRCULAR_DMA_en = DMA_SxCR_CIRC,
} DMA_CIRCULAR_e;

typedef struct DMAInit_s
{
    DMA_Stream_TypeDef* dmaStream;
    DMA_ChannelSelect_e channel;
    MemoryInc_e memoryInc;
    PeriphInc_e periphInc;
    uint32_t periphBaseAddress;
    uint32_t memoryBaseAddress;
    uint16_t bufferSize;
    DMA_Dir_e direction;
    DMA_MSIZE_e msize;
    DMA_PSIZE_e psize;
    DMA_TransferComplete_e completeIrq;
    DMA_FLOWCONTROL_e flowControl;
    DMA_CIRCULAR_e  circularDma;
}DMAInit_s;

void dma_init(const DMAInit_s* init_s);

void dma_enablexfer(void);

#endif
