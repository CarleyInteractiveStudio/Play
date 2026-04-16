/* Linker Script para Carley Play (ARM926EJ-S) */

ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x60000000, LENGTH = 256M
}

SECTIONS
{
    . = 0x60000000;

    .text :
    {
        *(.vectors)
        *(.text*)
        *(.rodata*)
    } > RAM

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > RAM

    .stack :
    {
        . = ALIGN(8);
        . = . + 0x4000; /* 16KB stack */
        _stack_top = .;
    } > RAM
}
