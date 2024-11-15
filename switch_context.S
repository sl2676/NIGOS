    .section .text
    .global switch_context

switch_context:
    mov x2, sp          
    str x2, [x0]        

    ldr x2, [x1]       
    mov sp, x2         

    ret

