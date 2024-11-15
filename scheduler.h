#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <stddef.h>

void init_scheduler(void);
void schedule_process(process_t *proc);
void start_scheduler(void);
void yield(void);

extern void switch_context(uint64_t *old_sp, uint64_t *new_sp); 

#endif 

