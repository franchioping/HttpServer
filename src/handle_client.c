//
// Created by franchioping on 6/24/24.
//

#include "handle_client.h"

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/socket.h>


#include "util.h"

#define BUFF_SIZE 128
#define MAX_BUFF_SIZE 8192


bool check_if_request_end(char* data, ssize_t data_length){
    char* end = "\r\n\r\n";
    for(int i = 0; i < 4; i++){
        if(end[i] != data[data_length - 4 + i])
            return false;
    }
    return true;

}

char** request_get_lines_from_buff(const char* buff, size_t buff_len, int* lines_count){
    int line_count = 0;
    for(int i = 0; i < buff_len-1; i++){
        if(buff[i] == '\r' && buff[i+1]=='\n')
            line_count ++;
    }
    char** lines = (char**) malloc(sizeof(char*) * line_count);
    int line_start = 0;
    int line_num = 0;
    for(int i = 0; i < buff_len; i++){
        if(buff[i] == '\r' && buff[i+1]=='\n'){
            char* line = malloc(sizeof(char) * (i - line_start + 1));
            memcpy(line, &buff[line_start], i - line_start);
            line[i - line_start] = '\0';

            lines[line_num++] = line;

            line_start=i+2;
        }
    }
    *lines_count = line_count;
    return lines;
}

ssize_t receive_data(int client_fd, char** data){
    char* buff = (char*) malloc(BUFF_SIZE);
    int buff_size = BUFF_SIZE;
    while(true){
        ssize_t msg_length = recv(client_fd, &buff[buff_size-BUFF_SIZE], BUFF_SIZE, 0);
        if(msg_length == BUFF_SIZE){
            buff_size += BUFF_SIZE;
            if(buff_size > MAX_BUFF_SIZE){
                *data = nullptr;
                return -1;
            }
            char* temp = (char*) realloc(buff, buff_size);
            if(temp == NULL){
                *data = nullptr;
                return -1;
            }
            buff = temp;
        }
        if((msg_length < 0) || msg_length < BUFF_SIZE){
            ssize_t new_buff_size = buff_size - (BUFF_SIZE - msg_length);
            if(check_if_request_end(buff, new_buff_size)){
                char* temp = (char*) realloc(buff, buff_size);
                if(temp == NULL){
                    *data = buff;
                    return buff_size;
                }
                buff = temp;
                *data = buff;
                return new_buff_size;
            }
            return -1;
        }
    }
}


void handle_client(void* arg){
    int client_fd = *((int*) arg);

    // Set time-out on recv
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    if(setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) < 0)
        printf("setsockopt(SO_RCVTIMEO) Failed.");




    char* data;
    ssize_t data_length = receive_data(client_fd, &data);
    printf("Request Lenght: %lu\n", data_length);
    printf("Request:\n");

    int lines_count = 0;
    char** lines = request_get_lines_from_buff(data, data_length, &lines_count);

    for(int i = 0; i < lines_count; i++){
        char* line = lines[i];
        printf("    %s\n", line);

    }




    // Clean-Up

    for(int i = 0; i < lines_count; i++){
        free(lines[i]);
    }
    free(lines);
    free(data);
}