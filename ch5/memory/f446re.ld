MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

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
    } > RAM

    .bss :
    {
        _start_bss = .;
        *(.bss*)
        . = ALIGN(4);
        _end_bss = .;
        _end = .;
    } > RAM
}

_stack_size = 16K;
_mpu_size   = 4K;

/* top of RAM */
_end_stack = ORIGIN(RAM) + LENGTH(RAM);

/* lowest valid stack address */
_bottom_stack = _end_stack - _stack_size;

/* MPU guard region */
_start_guard = _bottom_stack - _mpu_size;

/* heap area */
_start_heap = _end;
_end_heap   = _start_guard;