/*
 * startup.s - Código de arranque para Carley Play (ARM)
 */

.section .vectors, "ax"
.global _start

_start:
    ldr pc, reset_addr
    ldr pc, undef_addr
    ldr pc, swi_addr
    ldr pc, prefetch_addr
    ldr pc, abort_addr
    nop
    ldr pc, irq_addr
    ldr pc, fiq_addr

reset_addr:     .word reset_handler
undef_addr:     .word loop
swi_addr:       .word loop
prefetch_addr:  .word loop
abort_addr:     .word loop
irq_addr:       .word loop
fiq_addr:       .word loop

loop: b loop

.section .text
reset_handler:
    /* 1. Inicializar el Stack Pointer (SP) */
    ldr sp, =_stack_top

    /* 2. Limpiar sección BSS */
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
bss_loop:
    cmp r0, r1
    strlt r2, [r0], #4
    blt bss_loop

    /* 3. Saltar al punto de entrada del kernel */
    bl _startup_entry
    b loop
