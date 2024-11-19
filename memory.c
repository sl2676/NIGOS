#include "memory.h"
#include "uart.h" 

#define MEMORY_POOL_SIZE (1024 * 1024)  

unsigned char memory_pool[MEMORY_POOL_SIZE]; 
size_t memory_pool_index = 0;

void *malloc(size_t size) {
    if (memory_pool_index + size > MEMORY_POOL_SIZE) {
        uart_puts("malloc: Out of memory!\n");
        return NULL;
    }
    void *ptr = &memory_pool[memory_pool_index];
    memory_pool_index += size;
    uart_puts("malloc: Allocated memory.\n");
    return ptr;
}

void free(void *ptr) {
    (void)ptr; 
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    for (size_t i = 0; i < n; i++) {
        p[i] = (unsigned char)c;
    }
    return s;
}

