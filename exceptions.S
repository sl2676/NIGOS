.section .text
.global vectors
vectors:
    b sync_exception     
    b irq_handler        
    b fiq_handler        
    b error_handler      

sync_exception:
    b hang

irq_handler:
    b hang

fiq_handler:
    b hang

error_handler:
    b hang

hang:
    wfi
    b hang

