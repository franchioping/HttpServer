//
// Created by franchioping on 6/25/24.
//

#ifndef HTTPSERVER_LINKEDLIST_H
#define HTTPSERVER_LINKEDLIST_H

#include <sys/types.h>

typedef struct listnode {
    struct listnode* next_node;
    void* data;
} listnode;

listnode* list_get_at_index(listnode* list_start, ssize_t index);
ssize_t list_get_length(listnode* list_start);
void list_free(listnode* list_start);




#endif //HTTPSERVER_LINKEDLIST_H
