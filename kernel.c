#include "uart.h"

void kernel_main(void) {
    uart_init();
    uart_puts("Kernel is running!\n");

    while (1) {
    	// fall asleep not!!
	}
}

