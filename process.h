#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define STACK_SIZE 4096

typedef enum {
    NEW,
    RUNNING,
    READY,
    TERMINATED
} process_state_t;

typedef struct process {
    uint64_t pid;
    uint64_t sp;                    
    uint64_t stack_base;             
    process_state_t state;
    struct process *next;            
    void (*entry_point)(void);       
} process_t;

extern process_t *current_process;   

void create_process(void (*entry_point)(void));
void process_start(void);            

#endif 

