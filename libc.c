#include "syscall.h"

static inline void syscall(int num, const void *arg) {
    asm volatile (
        "mov x0, %0\n"
        "mov x1, %1\n"
        "svc #0\n" 
        :
        : "r"(num), "r"(arg)
        : "x0", "x1"
    );
}

void syscall_write(const char *message) {
    syscall(SYSCALL_WRITE, message);
}

void syscall_yield() {
    syscall(SYSCALL_YIELD, NULL);
}

void syscall_exit() {
    syscall(SYSCALL_EXIT, NULL);
}

