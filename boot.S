.section .text
.global _start
_start:
    ldr x0, =_stack_top  
    mov sp, x0

    ldr x0, =vectors
    msr vbar_el1, x0

    bl kernel_main

hang:
    wfi
    b hang

