//
// Created by franchioping on 6/24/24.
//

#include "util.h"

#include <stdio.h>


void print_string(char* string, size_t string_len){
    for(int i = 0; i < string_len; i++){
        if(string[i] == '\r'){
            continue;
        }
        printf("%c", string[i]);
    }
}