#include "scheduler.h"
#include "uart.h"

process_t *current_process = NULL; 
static process_t *process_queue = NULL;

void init_scheduler(void) {
    uart_puts("Initializing scheduler...\n");
    process_queue = NULL;
    current_process = NULL;
    uart_puts("Finishing scheduler...\n");
}

void schedule_process(process_t *proc) {
    uart_puts("Scheduling a new process...\n");
    proc->state = READY;
    proc->next = NULL;

    if (!process_queue) {
        process_queue = proc;
    } else {
        process_t *temp = process_queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = proc;
    }
}

void start_scheduler(void) {
    uart_puts("Starting scheduler...\n");
    if (!process_queue) {
        uart_puts("No processes to schedule.\n");
        return;
    }

    current_process = process_queue;
    current_process->state = RUNNING;

    uart_puts("Switching to first process...\n");

    uint64_t dummy_sp = 0;
    switch_context(&dummy_sp, &current_process->sp);
}

void yield(void) {
    uart_puts("Yielding...\n");
    process_t *prev_process = current_process;

    if (current_process->next) {
        current_process = current_process->next;
    } else {
        current_process = process_queue;
    }

    uart_puts("Switching context...\n");
    prev_process->state = READY;
    current_process->state = RUNNING;

    switch_context(&prev_process->sp, &current_process->sp);
}

