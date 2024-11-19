.section .text
.global vectors
.global uart_puts
.extern timer_interrupt_handler 

vectors:
    b sync_exception     
    b irq_handler        
    b fiq_handler        
    b error_handler      

sync_exception:
    ldr x0, =msg_sync_exception
    bl uart_puts
    b hang

irq_handler:
    ldr x0, =msg_irq_handler
    bl uart_puts
    bl timer_interrupt_handler  
    eret                        

fiq_handler:
    ldr x0, =msg_fiq_handler
    bl uart_puts
    b hang

error_handler:
    ldr x0, =msg_error_handler
    bl uart_puts
    b hang

hang:
    wfi
    b hang

.section .rodata
msg_sync_exception:
    .asciz "Synchronous Exception\n"
msg_irq_handler:
    .asciz "IRQ Exception\n"
msg_fiq_handler:
    .asciz "FIQ Exception\n"
msg_error_handler:
    .asciz "Error Exception\n"
