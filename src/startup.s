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
irq_addr:       .word irq_wrapper
fiq_addr:       .word loop
loop:
    b loop
irq_wrapper:
    push {r0-r12, lr}
    bl gic_handler
    pop {r0-r12, lr}
    subs pc, lr, #4
reset_handler:
    ldr sp, =_stack_top
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
bss_loop:
    cmp r0, r1
    strlo r2, [r0], #4
    blo bss_loop
    bl _startup_entry
    b loop
