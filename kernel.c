#include "scheduler.h"
#include "uart.h"     
#include <stdint.h>    


#define RUN_TIMER_PREEMPTION_TEST 1
#define RUN_PRIORITY_SCHEDULING_TEST 0
#define RUN_MAX_TASKS_TEST 0
#define RUN_TASK_TERMINATION_TEST 0

extern void sys_yield();
extern void sys_write(const char *str);
extern void sys_exit();



void configure_timer() {
    uint32_t timer_frequency = 62500; 
    uart_puts("Configuring timer...\n");

    asm volatile("msr cntfrq_el0, %0" :: "r"(timer_frequency));

    uint32_t timer_interval = 10000;
    asm volatile("msr cntp_tval_el0, %0" :: "r"(timer_interval));

    uint32_t enable_timer = 1; 
    asm volatile("msr cntp_ctl_el0, %0" :: "r"(enable_timer));

    uart_puts("Timer configured.\n");

    
    asm volatile("msr daifclr, #2");
    uart_puts("IRQ enabled.\n");
}


void test_task1() {
    while (1) {
        sys_write("Task 1 is running.\n");
        for (volatile int i = 0; i < 1000000; i++); 
        sys_write("Task 1 yielding.\n");
        sys_yield();
    }
}

void test_task2() {
    while (1) {
        sys_write("Task 2 is running.\n");
        for (volatile int i = 0; i < 1000000; i++); 
        sys_write("Task 2 yielding.\n");
        sys_yield();
    }
}

void test_exit_task() {
    sys_write("Task with exit system call is running.\n");
    for (volatile int i = 0; i < 500000; i++); 
    sys_write("Task with exit system call terminating.\n");
    sys_exit();
}

void test_max_tasks() {
    for (int i = 0; i < MAX_TASKS + 1; i++) {
        uart_puts("Adding task ");
        uart_putint(i);
        uart_puts("...\n");
        scheduler_add_task(idle_task, i % 3);
    }
}

void test_priority_scheduling() {
    scheduler_add_task(test_task1, 2); 
    scheduler_add_task(test_task2, 3); 
    scheduler_add_task(test_exit_task, 1); 
}

void test_task_termination() {
    scheduler_add_task(test_exit_task, 2);
    scheduler_add_task(test_task1, 1);
}

void test_timer_preemption() {
    scheduler_add_task(test_task1, 1);
    scheduler_add_task(test_task2, 2);
    configure_timer();
}


void kernel_main() {
    uart_init();
    uart_puts("Kernel is running!\n");

    scheduler_init();

#if RUN_TIMER_PREEMPTION_TEST
    uart_puts("Running Test: Timer Preemption\n");
    test_timer_preemption();
#endif

#if RUN_PRIORITY_SCHEDULING_TEST
    uart_puts("Running Test: Priority Scheduling\n");
    test_priority_scheduling();
#endif

#if RUN_MAX_TASKS_TEST
    uart_puts("Running Test: Max Tasks\n");
    test_max_tasks();
#endif

#if RUN_TASK_TERMINATION_TEST
    uart_puts("Running Test: Task Termination\n");
    test_task_termination();
#endif

    uart_puts("Starting Scheduler...\n");
    while (1) {
        schedule(); 
    }
}

