#include <stdint.h>

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
        if ((zeroed_variable_in_bss % 1000) == 0) {
            // asm volatile("svc 0");  // Триггерим SVC (опционально)
        }
    }
}

__attribute__ ((section(".isr_vector")))
void (* const IV[])(void) =
{
    // ========== 1. СИСТЕМНЫЕ ИСКЛЮЧЕНИЯ ==========
        // 0x0000 0000 - Начальное значение SP
    /* ===================== SYSTEM EXCEPTIONS ===================== */

    (void (*)(void))(&END_STACK),      // 0  - Initial Stack Pointer
    isr_reset,              // 1  - Reset
    isr_fault,              // 2  - NMI
    isr_fault,              // 3  - HardFault
    isr_fault,              // 4  - MemManage
    isr_fault,              // 5  - BusFault
    isr_fault,              // 6  - UsageFault

    0,0,0,0,                // 7-10 Reserved

    isr_svc,                // 11 - SVCall
    isr_empty,              // 12 - Debug Monitor
    0,                      // 13 - Reserved
    isr_empty,              // 14 - PendSV
    isr_empty,              // 15 - SysTick

    /* ===================== IRQ0+ ===================== */

    isr_empty,  // IRQ0   WWDG1
    isr_empty,  // IRQ1   PVD_PVM
    isr_empty,  // IRQ2   RTC_TAMP_STAMP_CSS_LSE
    isr_empty,  // IRQ3   RTC_WKUP
    isr_empty,  // IRQ4   FLASH
    isr_empty,  // IRQ5   RCC
    isr_empty,  // IRQ6   EXTI0
    isr_empty,  // IRQ7   EXTI1
    isr_empty,  // IRQ8   EXTI2
    isr_empty,  // IRQ9   EXTI3
    isr_empty,  // IRQ10  EXTI4
    isr_empty,  // IRQ11  DMA1_STR0
    isr_empty,  // IRQ12  DMA1_STR1
    isr_empty,  // IRQ13  DMA1_STR2
    isr_empty,  // IRQ14  DMA1_STR3
    isr_empty,  // IRQ15  DMA1_STR4
    isr_empty,  // IRQ16  DMA1_STR5
    isr_empty,  // IRQ17  DMA1_STR6
    isr_empty,  // IRQ18  ADC1_2
    isr_empty,  // IRQ19  FDCAN1_IT0
    isr_empty,  // IRQ20  FDCAN2_IT0
    isr_empty,  // IRQ21  FDCAN1_IT1
    isr_empty,  // IRQ22  FDCAN2_IT1
    isr_empty,  // IRQ23  EXTI9_5
    isr_empty,  // IRQ24  TIM1_BRK
    isr_empty,  // IRQ25  TIM1_UP
    isr_empty,  // IRQ26  TIM1_TRG_COM
    isr_empty,  // IRQ27  TIM1_CC
    isr_empty,  // IRQ28  TIM2
    isr_empty,  // IRQ29  TIM3
    isr_empty,  // IRQ30  TIM4
    isr_empty,  // IRQ31  I2C1_EV
    isr_empty,  // IRQ32  I2C1_ER
    isr_empty,  // IRQ33  I2C2_EV
    isr_empty,  // IRQ34  I2C2_ER
    isr_empty,  // IRQ35  SPI1
    isr_empty,  // IRQ36  SPI2
    isr_empty,  // IRQ37  USART1
    isr_empty,  // IRQ38  USART2
    isr_empty,  // IRQ39  USART3
    isr_empty,  // IRQ40  EXTI15_10
    isr_empty,  // IRQ41  RTC_ALARM
    0,           // IRQ42  RESERVED
    isr_empty,  // IRQ43  TIM8_BRK_TIM12
    isr_empty,  // IRQ44  TIM8_UP_TIM13
    isr_empty,  // IRQ45  TIM8_TRG_COM_TIM14
    isr_empty,  // IRQ46  TIM8_CC
    isr_empty,  // IRQ47  DMA1_STR7
    isr_empty,  // IRQ48  FMC
    isr_empty,  // IRQ49  SDMMC1
    isr_empty,  // IRQ50  TIM5
    isr_empty,  // IRQ51  SPI3
    isr_empty,  // IRQ52  UART4
    isr_empty,  // IRQ53  UART5
    isr_empty,  // IRQ54  TIM6_DAC
    isr_empty,  // IRQ55  TIM7
    isr_empty,  // IRQ56  DMA2_STR0
    isr_empty,  // IRQ57  DMA2_STR1
    isr_empty,  // IRQ58  DMA2_STR2
    isr_empty,  // IRQ59  DMA2_STR3
    isr_empty,  // IRQ60  DMA2_STR4
    isr_empty,  // IRQ61  ETH
    isr_empty,  // IRQ62  ETH_WKUP
    isr_empty,  // IRQ63  FDCAN_CAL
    isr_empty,  // IRQ64  CM7_SEV
    isr_empty,  // IRQ65  CM4_SEV
    0,           // IRQ66  RESERVED
    0,           // IRQ67  RESERVED
    isr_empty,  // IRQ68  DMA2_STR5
    isr_empty,  // IRQ69  DMA2_STR6
    isr_empty,  // IRQ70  DMA2_STR7
    isr_empty,  // IRQ71  USART6
    isr_empty,  // IRQ72  I2C3_EV
    isr_empty,  // IRQ73  I2C3_ER
    isr_empty,  // IRQ74  OTG_HS_EP1_OUT
    isr_empty,  // IRQ75  OTG_HS_EP1_IN
    isr_empty,  // IRQ76  OTG_HS_WKUP
    isr_empty,  // IRQ77  OTG_HS
    isr_empty,  // IRQ78  DCMI
    isr_empty,  // IRQ79  CRYP
    isr_empty,  // IRQ80  HASH_RNG
    isr_empty,  // IRQ81  FPU
    isr_empty,  // IRQ82  UART7
    isr_empty,  // IRQ83  UART8
    isr_empty,  // IRQ84  SPI4
    isr_empty,  // IRQ85  SPI5
    isr_empty,  // IRQ86  SPI6
    isr_empty,  // IRQ87  SAI1
    isr_empty,  // IRQ88  LTDC
    isr_empty,  // IRQ89  LTDC_ER
    isr_empty,  // IRQ90  DMA2D
    isr_empty,  // IRQ91  SAI2
    isr_empty,  // IRQ92  QUADSPI
    isr_empty,  // IRQ93  LPTIM1
    isr_empty,  // IRQ94  CEC
    isr_empty,  // IRQ95  I2C4_EV
    isr_empty,  // IRQ96  I2C4_ER
    isr_empty,  // IRQ97  SPDIF
    isr_empty,  // IRQ98  OTG_FS_EP1_OUT
    isr_empty,  // IRQ99  OTG_FS_EP1_IN
    isr_empty,  // IRQ100 OTG_FS_WKUP
    isr_empty,  // IRQ101 OTG_FS
    isr_empty,  // IRQ102 DMAMUX1_OVR
    isr_empty,  // IRQ103 HRTIM1_MST
    isr_empty,  // IRQ104 HRTIM1_TIMA
    isr_empty,  // IRQ105 HRTIM1_TIMB
    isr_empty,  // IRQ106 HRTIM1_TIMC
    isr_empty,  // IRQ107 HRTIM1_TIMD
    isr_empty,  // IRQ108 HRTIM1_TIME
    isr_empty,  // IRQ109 HRTIM1_FLT
    isr_empty,  // IRQ110 DFSDM1_FLT0
    isr_empty,  // IRQ111 DFSDM1_FLT1
    isr_empty,  // IRQ112 DFSDM1_FLT2
    isr_empty,  // IRQ113 DFSDM1_FLT3
    isr_empty,  // IRQ114 SAI3
    isr_empty,  // IRQ115 SWPMI1
    isr_empty,  // IRQ116 TIM15
    isr_empty,  // IRQ117 TIM16
    isr_empty,  // IRQ118 TIM17
    isr_empty,  // IRQ119 MDIOS_WKUP
    isr_empty,  // IRQ120 MDIOS
    isr_empty,  // IRQ121 JPEG
    isr_empty,  // IRQ122 MDMA
    isr_empty,  // IRQ123 DSI
    isr_empty,  // IRQ124 SDMMC2
    isr_empty,  // IRQ125 HSEM0
    isr_empty,  // IRQ126 HSEM1
    isr_empty,  // IRQ127 ADC3
    isr_empty,  // IRQ128 DMAMUX2_OVR
    isr_empty,  // IRQ129 BDMA_CH0
    isr_empty,  // IRQ130 BDMA_CH1
    isr_empty,  // IRQ131 BDMA_CH2
    isr_empty,  // IRQ132 BDMA_CH3
    isr_empty,  // IRQ133 BDMA_CH4
    isr_empty,  // IRQ134 BDMA_CH5
    isr_empty,  // IRQ135 BDMA_CH6
    isr_empty,  // IRQ136 BDMA_CH7
    isr_empty,  // IRQ137 COMP
    isr_empty,  // IRQ138 LPTIM2
    isr_empty,  // IRQ139 LPTIM3
    isr_empty,  // IRQ140 LPTIM4
    isr_empty,  // IRQ141 LPTIM5
    isr_empty,  // IRQ142 LPUART
    isr_empty,  // IRQ143 WWDG2_RST
    isr_empty,  // IRQ144 CRS
    isr_empty,  // IRQ145 ECC
    isr_empty,  // IRQ146 SAI4
    0,           // IRQ147 RESERVED
    isr_empty,  // IRQ148 HOLD_CORE
    isr_empty   // IRQ149 WKUP
};