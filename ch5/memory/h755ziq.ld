MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    AXI_SRAM (rwx) : ORIGIN = 0x24000000 , LENGTH = 512K
    DTCM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_stack_size = 16 * 1024;

SECTIONS
{
    .text :
    {
        _start_text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _end_text = .;
    } > FLASH

    _stored_data = .;
    .data : AT (_stored_data)
    {
        _start_data = .;
        *(.data*)
        . = ALIGN(4);
        _end_data = .;
    } > AXI_SRAM

    .bss :
    {
        _start_bss = .;
        *(.bss*)
        . = ALIGN(4);
        _end_bss = .;
        _end = .;
    } > AXI_SRAM

    .stack :
    {
        . = ORIGIN(DTCM) + LENGTH(DTCM) - _stack_size;
        . = ALIGN(8);
        _start_stack = .;
        _end_stack = _start_stack + _stack_size;
    } > DTCM
}

/* Проверка, что не вышли за границы DTCM */
ASSERT(_end_stack <= ORIGIN(DTCM) + LENGTH(DTCM), "Stack exceeds DTCM!")