/* Linker Script para Carley Play (Ejemplo genérico para ARM926) */

ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 256M
}

SECTIONS
{
    .text :
    {
        *(.text*)
        *(.rodata*)
    } > RAM

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM

    .stack :
    {
        . = ALIGN(8);
        . = . + 0x4000; /* 16KB de Stack */
        _stack_top = .;
    } > RAM
}
