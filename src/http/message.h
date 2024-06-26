//
// Created by franchioping on 6/26/24.
//

#ifndef HTTPSERVER_MESSAGE_H
#define HTTPSERVER_MESSAGE_H


struct generic_message {
    char* start_line;
    char** message_headers;
    char* message_body;
};

#endif //HTTPSERVER_MESSAGE_H
