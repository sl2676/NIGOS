#include "process.h"
#include "memory.h"
#include "scheduler.h"
#include "uart.h"

static uint64_t pid_counter = 1;      
process_t *current_process = NULL;   

void create_process(void (*entry_point)(void)) {
    uart_puts("Entering create_process()\n");

    process_t *proc = (process_t *)malloc(sizeof(process_t));
    if (!proc) {
        uart_puts("Failed to allocate process structure.\n");
        return;
    }

    uart_puts("Allocated process structure.\n");

    proc->pid = pid_counter++;
    proc->state = TASK_READY; 
    proc->entry_point = entry_point;

    proc->stack_base = (uint64_t)malloc(STACK_SIZE);
    if (!proc->stack_base) {
        uart_puts("Failed to allocate process stack.\n");
        return;
    }

    uart_puts("Allocated process stack.\n");

    proc->sp = proc->stack_base + STACK_SIZE;

    uint64_t *stack = (uint64_t *)proc->sp;

    stack = (uint64_t *)((uint64_t)(stack) & ~0xF);

    *(--stack) = (uint64_t)process_start; 

    uart_puts("Configured process stack.\n");

    proc->sp = (uint64_t)stack;

    Task task;
    task.stack_pointer = (uint64_t *)proc->sp;
    task.state = TASK_READY;
    task.entry_point = entry_point;

    schedule_process(&task);

    uart_puts("Exiting create_process()\n");
}

void process_start(void) {
    uart_puts("process_start: Starting process entry point.\n");
    if (current_process && current_process->entry_point) {
        current_process->entry_point();
    }

    uart_puts("Process has finished execution.\n");
    current_process->state = TASK_TERMINATED;

    while (1) {
    }
}

