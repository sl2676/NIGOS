#include "uart.h"

#define UART0_BASE 0x09000000
#define UART_FR (UART0_BASE + 0x18)
#define UART_DR (UART0_BASE + 0x00)

void uart_init() {
	// init baud stuff and other stuff
}

void uart_putc(char c) {
    while (*(volatile unsigned int *)UART_FR & (1 << 5)); 
    *(volatile unsigned int *)UART_DR = c;
}

void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

