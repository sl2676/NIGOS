#include "fs.h"

Node *root;

void fs_init(void) {
    root = (Node *)malloc(sizeof(Node));
    if (!root) {
        uart_puts("Failed to initialize filesystem: Out of memory\n");
        return;
    }
    root->type = DIRECTORY_TYPE;
    strcpy(root->directory.name, "/");
    root->directory.child_count = 0;
}

Node *create_file(const char *name, const char *content, uint32_t size, Node *parent) {
    if (parent->type != DIRECTORY_TYPE) {
        return NULL;
    }
    if (parent->directory.child_count >= MAX_FILES) {
        return NULL;
    }

    Node *file_node = (Node *)malloc(sizeof(Node));
    if (!file_node) {
        uart_puts("Failed to create file: Out of memory\n");
        return NULL;
    }
    file_node->type = FILE_TYPE;
    strncpy(file_node->file.name, name, MAX_FILENAME);
    file_node->file.size = size;
    memcpy(file_node->file.data, content, size);

    parent->directory.children[parent->directory.child_count++] = file_node;
    return file_node;
}

Node *create_directory(const char *name, Node *parent) {
    if (parent->type != DIRECTORY_TYPE) {
        return NULL;
    }
    if (parent->directory.child_count >= MAX_FILES) {
        return NULL;
    }

    Node *dir_node = (Node *)malloc(sizeof(Node));
    if (!dir_node) {
        uart_puts("Failed to create directory: Out of memory\n");
        return NULL;
    }
    dir_node->type = DIRECTORY_TYPE;
    strncpy(dir_node->directory.name, name, MAX_FILENAME);
    dir_node->directory.child_count = 0;

    parent->directory.children[parent->directory.child_count++] = dir_node;
    return dir_node;
}

void list_directory(Node *directory) {
    if (directory->type != DIRECTORY_TYPE) {
        uart_puts("Not a directory.\n");
        return;
    }
    for (uint32_t i = 0; i < directory->directory.child_count; i++) {
        Node *child = directory->directory.children[i];
        uart_puts(child->type == DIRECTORY_TYPE ? "DIR  " : "FILE ");
        uart_puts(child->type == DIRECTORY_TYPE ? child->directory.name : child->file.name);
        uart_puts("\n");
    }
}

Node *find_node(const char *name, Node *directory) {
    if (directory->type != DIRECTORY_TYPE) {
        return NULL;
    }
    for (uint32_t i = 0; i < directory->directory.child_count; i++) {
        Node *child = directory->directory.children[i];
        const char *child_name = (child->type == DIRECTORY_TYPE) ? child->directory.name : child->file.name;
        if (strncmp(name, child_name, MAX_FILENAME) == 0) {
            return child;
        }
    }
    return NULL;
}

