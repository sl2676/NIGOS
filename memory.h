#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *malloc(size_t size);
void free(void *ptr);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

#endif 

