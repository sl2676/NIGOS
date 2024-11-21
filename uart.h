#ifndef UART_H
#define UART_H
#include <stdint.h>

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *str);
void uart_printf(const char *format, ...);
void uart_putint(int num);
void uart_puthex(uint64_t value);

#endif 

