//
// Created by franchioping on 6/24/24.
//

#include "handle_client.h"

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/socket.h>


#include "util.h"


#define BUFFER_SIZE 256

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

void handle_client(void* arg){
    int client_fd = *((int*) arg);

    char* buff = (char*) malloc(BUFFER_SIZE * sizeof(char));

    ssize_t bytes_received = recv(client_fd, buff, BUFFER_SIZE, 0);
    if(bytes_received < 0){
        printf("Failed to receive.\n");
        return;
    }

    // Print Request
    printf("Bytes Received: %lu\n", bytes_received);
    printf("Request:\n");

    //print_string(buff, bytes_received);

    int lines_count = 0;
    char** lines = request_get_lines_from_buff(buff, bytes_received, &lines_count);

    for(int i = 0; i < lines_count; i++){
        char* line = lines[i];
        printf("%s\n", line);
        free(line);
    }
    printf("\n");

    free(lines);
}