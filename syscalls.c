#include "syscalls.h"

void syscall_write(const char *msg) {
    register uint64_t x0 asm("x0") = SYSCALL_WRITE;
    register const char *x1 asm("x1") = msg;
    asm volatile("svc #0" :: "r"(x0), "r"(x1));
}

void syscall_yield(void) {
    register uint64_t x0 asm("x0") = SYSCALL_YIELD;
    asm volatile("svc #0" :: "r"(x0));
}

void *syscall_malloc(size_t size) {
    register uint64_t x0 asm("x0") = SYSCALL_MALLOC;
    register size_t x1 asm("x1") = size;
    void *result;
    asm volatile("svc #0" :: "r"(x0), "r"(x1));
    asm volatile("mov %0, x0" : "=r"(result));
    return result;
}

void sys_yield() {
}

void sys_exit() {
}
