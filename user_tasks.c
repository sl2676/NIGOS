#include "syscall.h"

void user_task1() {
    while (1) {
        syscall_write("User Task 1 is running.\n");
        for (volatile int i = 0; i < 1000000; i++); 
        syscall_yield();
    }
}

void user_task2() {
    while (1) {
        syscall_write("User Task 2 is running.\n");
        for (volatile int i = 0; i < 1000000; i++); 
        syscall_yield();
    }
}

