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
        tasks[i].priority = 0;          
    }
    current_task = -1; 
    num_tasks = 0;     
    uart_puts("Adding idle task...\n");
    scheduler_add_task(idle_task, 0);
}

void scheduler_add_task(void (*entry_point)(void), int priority) {
    if (num_tasks >= MAX_TASKS) {
        uart_puts("Error: Maximum tasks reached!\n");
        return;
    }

	uart_puts("Task Debug: Initializing Task...\n");

    Task *task = &tasks[num_tasks];
    task->entry_point = entry_point;
    task->state = TASK_READY;
    task->priority = priority;


    uint64_t *stack = &task->stack[TASK_STACK_SIZE - 1]; 
     // x30 (LR)
    *(--stack) = 0;                      
    // ELR_EL1
    *(--stack) = (uint64_t)entry_point;  
     // SPSR_EL1
    *(--stack) = 0x0;                     
    task->stack_pointer = stack;

    num_tasks++;

	uart_puts("Task stack pointer: ");
	uart_puthex((uint64_t)task->stack_pointer);
	uart_puts("\n");
	uart_puts("Task entry point: ");
	uart_puthex((uint64_t)task->entry_point);
	uart_puts("\n");

    uart_puts("Task added successfully!\n");
}


void scheduler_remove_task(int task_id) {
    if (task_id < 0 || task_id >= num_tasks) {
        uart_puts("Error: Invalid task ID for removal.\n");
        return;
    }

    uart_puts("Removing Task ");
    uart_putint(task_id);
    uart_puts("\n");

  
    free(tasks[task_id].stack_pointer);

    for (int i = task_id; i < num_tasks - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    num_tasks--;
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
        idle_task();
        return;
    }

	uart_puts("Scheduler Debug: Task States and Priorities:\n");
    int highest_priority = -1;
    int next_task = -1;

    
	for (int i = 0; i < num_tasks; i++) {
        uart_puts("Checking Task ");
        uart_putint(i);
        uart_puts(", State: ");
        uart_putint(tasks[i].state);
        uart_puts(", Priority: ");
        uart_putint(tasks[i].priority);
        uart_puts("\n");

        if (tasks[i].state == TASK_READY && tasks[i].priority > highest_priority) {
            highest_priority = tasks[i].priority;
            next_task = i;
        }
    }

    if (next_task == -1) {
        uart_puts("No ready tasks. Running idle task.\n");
        idle_task();
        return;
    }

    int prev_task = current_task;
    current_task = next_task;

    
    uart_puts("Task Switch: ");
    uart_puts("Prev Task: ");
    if (prev_task != -1) {
        uart_putint(prev_task);
    } else {
        uart_puts("None");
    }
    uart_puts(", Current Task: ");
    uart_putint(current_task);
    uart_puts(", Priority: ");
    uart_putint(tasks[current_task].priority);
    uart_puts("\n");

   
    if (prev_task != -1 && tasks[prev_task].state == TASK_RUNNING) {
        asm volatile("mov %0, sp" : "=r"(tasks[prev_task].stack_pointer) :: "memory");
        uart_puts("Saved stack pointer for Task ");
        uart_putint(prev_task);
        uart_puts("\n");
        tasks[prev_task].state = TASK_READY;
    }

   
    uart_puts("Loading stack pointer for Task ");
    uart_putint(current_task);
    uart_puts("\n");
    asm volatile("mov sp, %0" :: "r"(tasks[current_task].stack_pointer) : "memory");
    tasks[current_task].state = TASK_RUNNING;


    ((void (*)(void))tasks[current_task].entry_point)();
}





void sys_yield() {
	uart_puts("System call: Yield invoked.\n");
    uart_putint(current_task);
    uart_puts(".\n");
	asm volatile("mov x0, #0\n\t"
                 "svc #0\n\t");
}

void sys_write(const char *str) {
	uart_puts("System call: Write invoked with message: ");
	uart_putint(current_task);
    uart_puts(" with message: ");
    uart_puts(str);
    uart_puts("\n");
    asm volatile("mov x0, %0\n\t"
                 "mov x1, #1\n\t"
                 "svc #0\n\t" :: "r"(str));
}

void sys_exit() {
    uart_puts("System call: Exit\n");

    if (current_task != -1) {
        uart_puts("Task ");
        uart_putint(current_task);
        uart_puts(" is terminating.\n");

        tasks[current_task].state = TASK_TERMINATED;

      
        uart_puts("Task ");
        uart_putint(current_task);
        uart_puts(" marked as terminated.\n");

      
        schedule();
    } else {
        uart_puts("Error: No current task to terminate.\n");
    }
}




void timer_interrupt_handler() {
    uart_puts("Timer interrupt occurred. Initiating schedule.\n");


    if (current_task != -1 && tasks[current_task].state == TASK_RUNNING) {
        asm volatile("mov %0, sp" : "=r"(tasks[current_task].stack_pointer) :: "memory");
        uart_puts("Saved stack pointer for Task ");
        uart_putint(current_task);
        uart_puts("\n");
		tasks[current_task].state = TASK_READY;
    }


    uint32_t timer_interval = 10000;
    asm volatile("msr cntp_tval_el0, %0" :: "r"(timer_interval));

	uart_puts("Calling scheduler from timer interrupt.\n");
    schedule();
	uart_puts("Scheduler invoked from timer interrupt.\n");
}


void idle_task() {
    while (1) {
        uart_puts("Idle task active: waiting for tasks.\n");
        asm volatile("wfi"); 
    }
}

