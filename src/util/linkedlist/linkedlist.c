//
// Created by franchioping on 6/25/24.
//

#include <malloc.h>
#include <assert.h>
#include <memory.h>
#include "linkedlist.h"

listnode* lnkdList_NewNode(){
    listnode* node = (listnode*) malloc(sizeof(listnode));
    memset(node, 0, sizeof(listnode));
    return node;
}


listnode* lnkdList_FromPtrArray(const ssize_t length, void** data){

    listnode *start = lnkdList_NewNode();
    start->data = data[0];

    listnode* node = start;
    for(ssize_t i = 1; i < length; i++){
        node->next = lnkdList_NewNode();
        node = node->next;
        node->data = data[i];
    }
    return start;
}

listnode* lnkdList_FromIntArray(const ssize_t length, int* data){

    listnode *start = lnkdList_NewNode();
    start->data = &data[0];

    listnode* node = start;
    for(ssize_t i = 1; i < length; i++){
        node->next = lnkdList_NewNode();
        node = node->next;
        node->data = &data[i];
    }
    return start;
}


listnode* lnkdList_GetNth(listnode* head, ssize_t index){

    listnode* current = head;


    ssize_t count = 0;
    while (current != NULL) {
        if (count == index)
            return current;
        count++;
        current = current->next;
    }

    /* if we get to this line,
    the caller was asking
    for a non-existent element
    so we assert fail */
    assert(0);
}


ssize_t lnkdList_GetLength(listnode* head)
{
    listnode* cur = head;
    ssize_t size = 0;

    while (cur != NULL)
    {
        ++size;
        cur = cur->next;
    }

    return size;
}

void lnkdList_FreeDataInList(listnode* head){
    listnode* cur = head;
    while (cur != NULL)
    {
        free(cur->data);
        cur = cur->next;
    }

}

void lnkdList_Free(listnode* head){
    struct listnode* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

