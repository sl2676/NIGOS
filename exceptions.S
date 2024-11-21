.global vectors
.extern sys_yield
.extern sys_write
.extern sys_exit

vectors:
    b sync_exception       
    b irq_handler          
    b fiq_handler          
    b error_handler        

sync_exception:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    cmp x0, #0
    b.ne hang 

    mov x8, x0            
    cmp x8, #0
    b.eq sys_yield         
    cmp x8, #1
    b.eq sys_write         
    cmp x8, #2
    b.eq sys_exit         
    b hang                 


irq_handler:
    bl timer_interrupt_handler
    eret

fiq_handler:
    b hang

error_handler:
    b hang

hang:
    wfi
    b hang

