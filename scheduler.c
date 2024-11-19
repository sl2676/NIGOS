#include "scheduler.h"
#include "uart.h"
#include <stddef.h> 

static Task tasks[MAX_TASKS];
static int current_task = -1; 
static int num_tasks = 0;     

void scheduler_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].state = TASK_TERMINATED; 
        tasks[i].stack_pointer = NULL;  
        tasks[i].entry_point = NULL;    
    }
    current_task = -1;
    num_tasks = 0;     
    uart_puts("Adding idle task...\n");
    scheduler_add_task(idle_task);
}

void scheduler_add_task(void (*entry_point)(void)) {
    if (num_tasks >= MAX_TASKS) {
        uart_puts("Error: Maximum tasks reached!\n");
        return;
    }

    uart_puts("Initializing task...\n");

    Task *task = &tasks[num_tasks];
    task->entry_point = entry_point;
    task->state = TASK_READY;


    uint64_t *stack = &task->stack[TASK_STACK_SIZE - 1]; 
    *(--stack) = (uint64_t)entry_point;   
    task->stack_pointer = stack;

    num_tasks++;
    uart_puts("Task added successfully!\n");
}

void schedule_process(Task *new_task) {
    if (num_tasks >= MAX_TASKS) {
        uart_puts("Error: Cannot schedule more processes.\n");
        return;
    }

    uart_puts("Scheduling new process...\n");

    
    tasks[num_tasks] = *new_task;
    tasks[num_tasks].state = TASK_READY;

    num_tasks++;
    uart_puts("Process scheduled successfully.\n");
}

void schedule() {
    if (num_tasks == 0) {
        uart_puts("No tasks to schedule.\n");
        return;
    }

    int next_task = (current_task + 1) % num_tasks;

    
    uart_puts("Task States:\n");
    for (int i = 0; i < num_tasks; i++) {
        uart_puts("Task ");
        uart_putint(i);
        uart_puts(" state: ");
        uart_putint(tasks[i].state);
        uart_puts("\n");
    }

    
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[next_task].state == TASK_READY) {
            break;
        }
        next_task = (next_task + 1) % num_tasks;
    }

    if (tasks[next_task].state != TASK_READY) {
        uart_puts("No ready tasks. Running idle task.\n");
        idle_task();
        return;
    }

    int prev_task = current_task;
    current_task = next_task;

    uart_puts("Switching from Task ");
    uart_putint(prev_task);
    uart_puts(" to Task ");
    uart_putint(current_task);
    uart_puts("\n");

    if (prev_task != -1 && tasks[prev_task].state == TASK_RUNNING) {
        asm volatile("mov %0, sp" : "=r"(tasks[prev_task].stack_pointer) :: "memory");
        tasks[prev_task].state = TASK_READY;
    }

    asm volatile("mov sp, %0" :: "r"(tasks[current_task].stack_pointer) : "memory");
    tasks[current_task].state = TASK_RUNNING;

    
    uart_puts("Restoring SP for Task ");
    uart_putint(current_task);
    uart_puts(": ");
    uart_putint((uint64_t)tasks[current_task].stack_pointer);
    uart_puts("\n");

    
    uart_puts("Executing Task ");
    uart_putint(current_task);
    uart_puts("\n");
    ((void (*)(void))tasks[current_task].entry_point)();
}

void timer_interrupt_handler() {
    uart_puts("Timer interrupt occurred.\n");

    
    schedule();

    
    uint32_t timer_interval = 10000;
    asm volatile("msr cntp_tval_el0, %0" :: "r"(timer_interval));
}

void idle_task() {
    while (1) {
        uart_puts("Idle task running.\n");
        yield(); 
    }
}

void yield() {
    schedule();
}
