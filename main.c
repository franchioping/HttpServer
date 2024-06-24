#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <malloc.h>


#include "handle_client.h"


int main(void) {
    int serv_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(serv_sock_fd < 0){
        printf("Error while creating socket\n");
        return -1;
    }

    const int enable = 1;
    if (setsockopt(serv_sock_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        printf("setsockopt(SO_REUSEADDR) failed");
    printf("Created Socket File Descriptor Successfully.\n");



    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(serv_sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Couldn't bind to port\n");
        return -1;
    }
    printf("Socket Bound to Port Successfully.\n");



    if(listen(serv_sock_fd, 10) < 0){
        printf("Couldn't listen to socket\n");
        return -1;
    }
    printf("Socket Listening...\n");

    while(1){
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int *client_fd = malloc(sizeof(int));

        *client_fd = accept(serv_sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if(*client_fd < 0){
            perror("Accept failed\n");
            continue;
        }

        printf("================================\n");
        printf("Client Connected, Handling...\n");
        handle_client((void*) client_fd);

    }
    return 0;
}


