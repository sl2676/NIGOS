#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

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
    uint64_t stack[TASK_STACK_SIZE]; 
} Task;

void scheduler_init();
void scheduler_add_task(void (*entry_point)(void));
void schedule_process(Task *new_task);
void schedule();
void yield();
void idle_task();

#endif 
