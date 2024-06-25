cmake_minimum_required(VERSION 3.28)
project(HttpServer C)

set(CMAKE_C_STANDARD 23)

include_directories(".")


set(COMMON_SOURCES src/request/handle_client.c
        src/request/handle_client.h
        src/util/util.c
        src/util/util.h
        src/request/headers.c
        src/request/headers.h
        src/util/linkedlist/linkedlist.c
        src/util/linkedlist/linkedlist.h)

set(TARGET_SOURCES src/main.c)

set(TEST_SOURCES src/test/test_main.c
        src/test/linked_list.c
        src/test/linked_list.h)

add_executable(HttpServer ${COMMON_SOURCES} ${TARGET_SOURCES})

add_executable(tests ${COMMON_SOURCES} ${TEST_SOURCES})
target_link_libraries(tests -pthread -lcheck)

