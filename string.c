#include "string.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (*str++) len++;
    return len;
}

char *strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char *d = dest;
    size_t i = 0;
    while (i < n && src[i]) {
        d[i] = src[i];
        i++;
    }
    while (i < n) {
        d[i++] = '\0';
    }
    return dest;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n-- && *s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    if (n == (size_t)-1) {
        return 0;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

