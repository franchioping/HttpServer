cmake_minimum_required(VERSION 3.28)
project(HttpServer C)

set(CMAKE_C_STANDARD 23)

add_executable(HttpServer main.c
        handle_client.c
        handle_client.h
        util.c
        util.h)
