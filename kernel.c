#include "scheduler.h"
#include "uart.h"
#include <stdint.h>

void configure_timer() {
    uint32_t timer_frequency = 62500; 
    asm volatile("msr cntfrq_el0, %0" :: "r"(timer_frequency));

    uint32_t timer_interval = 10000; 
    asm volatile("msr cntp_tval_el0, %0" :: "r"(timer_interval));

    uint32_t enable_timer = 1; 
    asm volatile("msr cntp_ctl_el0, %0" :: "r"(enable_timer));

    asm volatile("msr daifclr, #2"); 
}

void test_task1() {
    while (1) {
        uart_puts("Task 1 is running.\n");
        for (volatile int i = 0; i < 1000000; i++); 
        uart_puts("Task 1 yielding.\n");
        yield();
    }
}

void test_task2() {
    while (1) {
        uart_puts("Task 2 is running.\n");
        for (volatile int i = 0; i < 1000000; i++);
        uart_puts("Task 2 yielding.\n");
        yield();
    }
}

void kernel_main() {
    uart_init();
    uart_puts("Kernel is running!\n");

    configure_timer(); 

    scheduler_init();

    uart_puts("Adding Task 1...\n");
    scheduler_add_task(test_task1);

    uart_puts("Adding Task 2...\n");
    scheduler_add_task(test_task2);

    uart_puts("Starting Scheduler...\n");
    while (1) {
        schedule(); 
    }
}
