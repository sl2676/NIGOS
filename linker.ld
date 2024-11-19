ENTRY(_start)

SECTIONS
{
    . = 0x40000000;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
        *(COMMON)
    }

    . = ALIGN(8);
    _stack_top = . + 0x10000; 
}
