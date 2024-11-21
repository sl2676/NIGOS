#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <stddef.h> 

#define SYSCALL_WRITE  0
#define SYSCALL_YIELD  1
#define SYSCALL_EXIT   2
#define SYSCALL_MALLOC 3

void syscall_write(const char *msg);
void syscall_yield(void);
void *syscall_malloc(size_t size);

#endif 

