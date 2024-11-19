#ifndef FS_H
#define FS_H

#include <stddef.h>
#include <stdint.h>
#include "memory.h"
#include "string.h"
#include "uart.h"

#define MAX_FILES       128
#define MAX_FILENAME    64
#define MAX_FILESIZE    1024  

typedef enum {
    FILE_TYPE,
    DIRECTORY_TYPE
} NodeType;

typedef struct Node Node;

typedef struct {
    char name[MAX_FILENAME];
    uint32_t size;
    char data[MAX_FILESIZE];
} File;

typedef struct {
    char name[MAX_FILENAME];
    Node *children[MAX_FILES];
    uint32_t child_count;
} Directory;

struct Node {
    NodeType type;
    union {
        File file;
        Directory directory;
    };
};

extern Node *root;

void fs_init(void);
Node *create_file(const char *name, const char *content, uint32_t size, Node *parent);
Node *create_directory(const char *name, Node *parent);
void list_directory(Node *directory);
Node *find_node(const char *name, Node *directory);

#endif 

