.section .text
.global _start

_start:
    ldr x0, =_stack_top
    mov sp, x0

    ldr x0, =vectors
    msr vbar_el1, x0

    mrs x0, CurrentEL
    lsr x0, x0, #2
    cmp x0, #1
    b.eq 1f
    mov x0, #0x3c5 
    msr spsr_el1, x0
    adr x0, 1f
    msr elr_el1, x0
    eret
1:
    bl kernel_main

hang:
    wfi
    b hang

