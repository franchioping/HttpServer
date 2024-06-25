//
// Created by franchioping on 6/25/24.
//

#include <malloc.h>
#include "linkedlist.h"


listnode* list_get_at_index(listnode* list_start, ssize_t index){
    listnode* node = list_start;
    for(int i = 0; i < index; i++){
        node = node->next_node;
    }
    return node;
}

ssize_t list_get_length(listnode* list_start){
    ssize_t length = 1;
    while(list_start->next_node){
        length++;
        list_start = list_start->next_node;
    }
    return length;
}

void list_free(listnode* list_start){
    if(list_start == NULL)
        return;
    listnode* head = list_start;
    listnode * tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next_node;
        free(tmp);
    }
}
