#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *str);
void uart_printf(const char *format, ...);
void uart_putint(int num);
#endif 

