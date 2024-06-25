cmake_minimum_required(VERSION 3.28)
project(HttpServer C)

set(CMAKE_C_STANDARD 23)

add_executable(HttpServer src/main.c
        src/handle_client.c
        src/handle_client.h
        src/util.c
        src/util.h)
