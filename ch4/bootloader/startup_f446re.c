#include <stdint.h>
#include "utils.h"

// ========== ОБЪЯВЛЕНИЯ СИМВОЛОВ ЛИНКЕРА ==========
extern uint32_t *END_STACK;
extern uint32_t _stored_data;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

// ========== ПЕРЕМЕННЫЕ В DATA И BSS ==========
static int zeroed_variable_in_bss;           // Будет в .bss
static int initialized_variable_in_data = 42; // Будет в .data

void main(void);
void isr_reset(void) {
    unsigned int *src, *dst;
    src = (unsigned int*)&_stored_data;
    dst = (unsigned int*)&_start_data;

    while (dst != (unsigned int*)&_end_data) {
        *dst = *src;
        dst++;
        src++;
    }

    dst = (unsigned int*)&_start_bss;
    while (dst != (unsigned int*)&_end_bss) {
        *dst = 0;
        dst++;
    }
    main();
}

void isr_fault(void) {
    /* Panic! */
    while (1);
}

void isr_svc(void) {
    /* empty */
}

void isr_empty(void) {
    /* empty */
}

void __attribute__((used, noreturn)) main(void) {
    while(1) {
        zeroed_variable_in_bss++;
        initialized_variable_in_data++;

        // Можно добавить условие (как в книге, но без utils_*)
        if ((zeroed_variable_in_bss % 2) == 0) {
            // asm volatile("svc 0");  // Триггерим SVC (опционально)
            utils_open();
            utils_close();
        }
    }
}

__attribute__ ((section(".isr_vector")))
void (* const IV[])(void) =
{
    // ========== 1. СИСТЕМНЫЕ ИСКЛЮЧЕНИЯ ==========
    (void (*)(void))(&END_STACK),    // 0x0000 0000 - Начальное значение SP
    isr_reset,                     // 0x0000 0004 - Reset
    isr_fault,                     // 0x0000 0008 - NMI
    isr_fault,                     // 0x0000 000C - HardFault
    isr_fault,                     // 0x0000 0010 - MemManage
    isr_fault,                     // 0x0000 0014 - BusFault
    isr_fault,                     // 0x0000 0018 - UsageFault
    0, 0, 0, 0,                    // 0x0000 001C-002B - 4x reserved
    isr_svc,                       // 0x0000 002C - SVCall
    isr_empty,                     // 0x0000 0030 - Debug Monitor
    0,                             // 0x0000 0034 - reserved
    isr_empty,                     // 0x0000 0038 - PendSV
    isr_empty,                     // 0x0000 003C - SysTick

    // ========== 2. ПЕРИФЕРИЙНЫЕ ПРЕРЫВАНИЯ (IRQ) ==========
    // Адреса с 0x0000 0040 (IRQ0) до 0x0000 0184 (IRQ81)

    isr_empty,  // IRQ0:  WWDG
    isr_empty,  // IRQ1:  PVD
    isr_empty,  // IRQ2:  TAMP_STAMP
    isr_empty,  // IRQ3:  RTC_WKUP
    isr_empty,  // IRQ4:  FLASH
    isr_empty,  // IRQ5:  RCC
    isr_empty,  // IRQ6:  EXTI0
    isr_empty,  // IRQ7:  EXTI1
    isr_empty,  // IRQ8:  EXTI2
    isr_empty,  // IRQ9:  EXTI3
    isr_empty,  // IRQ10: EXTI4
    isr_empty,  // IRQ11: DMA1_Stream0
    isr_empty,  // IRQ12: DMA1_Stream1
    isr_empty,  // IRQ13: DMA1_Stream2
    isr_empty,  // IRQ14: DMA1_Stream3
    isr_empty,  // IRQ15: DMA1_Stream4
    isr_empty,  // IRQ16: DMA1_Stream5
    isr_empty,  // IRQ17: DMA1_Stream6
    isr_empty,  // IRQ18: ADC
    isr_empty,  // IRQ19: CAN1_TX
    isr_empty,  // IRQ20: CAN1_RX0
    isr_empty,  // IRQ21: CAN1_RX1
    isr_empty,  // IRQ22: CAN1_SCE
    isr_empty,  // IRQ23: EXTI9_5
    isr_empty,  // IRQ24: TIM1_BRK_TIM9
    isr_empty,  // IRQ25: TIM1_UP_TIM10
    isr_empty,  // IRQ26: TIM1_TRG_COM_TIM11
    isr_empty,  // IRQ27: TIM1_CC
    isr_empty,  // IRQ28: TIM2
    isr_empty,  // IRQ29: TIM3
    isr_empty,  // IRQ30: TIM4
    isr_empty,  // IRQ31: I2C1_EV
    isr_empty,  // IRQ32: I2C1_ER
    isr_empty,  // IRQ33: I2C2_EV
    isr_empty,  // IRQ34: I2C2_ER
    isr_empty,  // IRQ35: SPI1
    isr_empty,  // IRQ36: SPI2
    isr_empty,  // IRQ37: USART1
    isr_empty,  // IRQ38: USART2
    isr_empty,  // IRQ39: USART3
    isr_empty,  // IRQ40: EXTI15_10
    isr_empty,  // IRQ41: RTC_Alarm
    isr_empty,  // IRQ42: OTG_FS_WKUP
    isr_empty,  // IRQ43: TIM8_BRK_TIM12
    isr_empty,  // IRQ44: TIM8_UP_TIM13
    isr_empty,  // IRQ45: TIM8_TRG_COM_TIM14
    isr_empty,  // IRQ46: TIM8_CC
    isr_empty,  // IRQ47: DMA1_Stream7
    isr_empty,  // IRQ48: FSMC        (F446RE — нет FSMC! Это пустышка)
    isr_empty,  // IRQ49: SDIO
    isr_empty,  // IRQ50: TIM5
    isr_empty,  // IRQ51: SPI3
    isr_empty,  // IRQ52: UART4
    isr_empty,  // IRQ53: UART5
    isr_empty,  // IRQ54: TIM6_DAC
    isr_empty,  // IRQ55: TIM7
    isr_empty,  // IRQ56: DMA2_Stream0
    isr_empty,  // IRQ57: DMA2_Stream1
    isr_empty,  // IRQ58: DMA2_Stream2
    isr_empty,  // IRQ59: DMA2_Stream3
    isr_empty,  // IRQ60: DMA2_Stream4
    isr_empty,  // IRQ61: ETHERNET     (F446RE — нет Ethernet! Пустышка)
    isr_empty,  // IRQ62: ETH_WKUP     (F446RE — нет Ethernet! Пустышка)
    isr_empty,  // IRQ63: CAN2_TX
    isr_empty,  // IRQ64: CAN2_RX0
    isr_empty,  // IRQ65: CAN2_RX1
    isr_empty,  // IRQ66: CAN2_SCE
    isr_empty,  // IRQ67: OTG_FS
    isr_empty,  // IRQ68: DMA2_Stream5
    isr_empty,  // IRQ69: DMA2_Stream6
    isr_empty,  // IRQ70: DMA2_Stream7
    isr_empty,  // IRQ71: USART6
    isr_empty,  // IRQ72: I2C3_EV
    isr_empty,  // IRQ73: I2C3_ER
    isr_empty,  // IRQ74: OTG_HS_EP1_OUT (F446RE — нет HS OTG! Пустышка)
    isr_empty,  // IRQ75: OTG_HS_EP1_IN  (F446RE — нет HS OTG! Пустышка)
    isr_empty,  // IRQ76: OTG_HS_WKUP    (F446RE — нет HS OTG! Пустышка)
    isr_empty,  // IRQ77: OTG_HS         (F446RE — нет HS OTG! Пустышка)
    isr_empty,  // IRQ78: DCMI           (F446RE — нет DCMI! Пустышка)
    isr_empty,  // IRQ79: CRYP           (F446RE — нет CRYP! Пустышка)
    isr_empty,  // IRQ80: HASH_RNG
    isr_empty   // IRQ81: FPU
};