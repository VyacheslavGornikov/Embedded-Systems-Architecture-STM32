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

_stack_size = 1024 * 16;
_start_heap = _end;
_end_heap = ORIGIN(RAM) + LENGTH(RAM) - _stack_size;
END_STACK = ORIGIN(RAM) + LENGTH(RAM);