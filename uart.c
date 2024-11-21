#include "uart.h"
#include <stdarg.h>  
#define UART0_BASE 0x09000000
#define UART_FR (UART0_BASE + 0x18)
#define UART_DR (UART0_BASE + 0x00)

void uart_init() {
    
}

void uart_putc(char c) {
    while (*(volatile unsigned int *)UART_FR & (1 << 5)); 
    *(volatile unsigned int *)UART_DR = c;
}
void uart_puts(const char *str) {
	if (!str || *str == '\0') return;
    while (*str) {
        uart_putc(*str++);
    }
}

void uart_printf(const char *format, ...) {
    const char *hex = "0123456789ABCDEF";
    char buffer[128];
    char *buf = buffer;

    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%' && *(format + 1)) {
            format++;
            if (*format == 'c') {
                char c = (char)va_arg(args, int);
                *buf++ = c;
            } else if (*format == 's') {
                const char *str = va_arg(args, const char *);
                while (*str) {
                    *buf++ = *str++;
                }
            } else if (*format == 'x' || *format == 'X') {
                unsigned int num = va_arg(args, unsigned int);
                for (int i = 28; i >= 0; i -= 4) {
                    *buf++ = hex[(num >> i) & 0xF];
                }
            }
        } else {
            *buf++ = *format;
        }
        format++;
    }

    *buf = '\0';  
    va_end(args);

    uart_puts(buffer);
}

void uart_putint(int num) {
    char buffer[12];
    int i = 10;
    buffer[11] = '\0';

    if (num == 0) {
        uart_puts("0");
        return;
    }

    int is_negative = (num < 0);
    if (is_negative) {
        num = -num;
    }

    while (num > 0 && i >= 0) {
        buffer[i--] = '0' + (num % 10);
        num /= 10;
    }

    if (is_negative) {
        buffer[i--] = '-';
    }

    uart_puts(&buffer[i + 1]);
}

void uart_puthex(uint64_t value) {
    const char *hex_digits = "0123456789ABCDEF";
    char buffer[17]; 
    buffer[16] = '\0'; 

    for (int i = 15; i >= 0; i--) {
        buffer[i] = hex_digits[value & 0xF]; 
        value >>= 4; 
    }

    uart_puts("0x");
    uart_puts(buffer);
}


void delay(volatile unsigned int count) {
    while (count--) {
        asm volatile("nop");
    }
}
