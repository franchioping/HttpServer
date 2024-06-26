//
// Created by franchioping on 6/25/24.
//

#ifndef HTTPSERVER_LINKEDLIST_H
#define HTTPSERVER_LINKEDLIST_H

#include <sys/types.h>

typedef struct listnode {
    struct listnode* next;
    void* data;
} listnode;

listnode* lnkdList_GetNth(listnode* head, ssize_t index);
ssize_t lnkdList_GetLength(listnode* head);
void lnkdList_Free(listnode* head);


listnode* lnkdList_FromIntArray(ssize_t length, int* data);
listnode* lnkdList_FromPtrArray(ssize_t length, void** data);

#endif //HTTPSERVER_LINKEDLIST_H
