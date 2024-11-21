#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "memory.h"

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_TERMINATED
} TaskState;

#define KERNEL_MODE 0
#define USER_MODE 1
#define MAX_TASKS 10
#define TASK_STACK_SIZE 1024

typedef struct Task {
    uint64_t *stack_pointer;
    void (*entry_point)(void);
    TaskState state;
    int privilege;
    int priority;                  
    uint64_t stack[TASK_STACK_SIZE];
} Task;

void scheduler_init();
void scheduler_add_task(void (*entry_point)(void), int priority);
void schedule();
void schedule_process(Task *new_task);
void sys_yield();
void sys_write(const char *str);
void sys_exit();
void idle_task();

#endif 

