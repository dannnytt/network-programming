cmake_minimum_required(VERSION 3.28)
project(udp_chat C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(client_sources
    ${CMAKE_SOURCE_DIR}/client/src/udp_client_init.c
    ${CMAKE_SOURCE_DIR}/client/src/udp_client_run.c
    ${CMAKE_SOURCE_DIR}/client/src/udp_client_send_msg.c
    ${CMAKE_SOURCE_DIR}/client/src/udp_client_recv_msg.c
    ${CMAKE_SOURCE_DIR}/client/src/udp_client_destroy.c
    ${CMAKE_SOURCE_DIR}/client/src/threads/udp_client_send_thread.c
    ${CMAKE_SOURCE_DIR}/client/src/threads/udp_client_recv_thread.c
    ${CMAKE_SOURCE_DIR}/client/main.c
)

set(server_sources
    ${CMAKE_SOURCE_DIR}/server/src/udp_server_init.c
    ${CMAKE_SOURCE_DIR}/server/src/udp_server_run.c
    ${CMAKE_SOURCE_DIR}/server/src/udp_server_sendto.c
    ${CMAKE_SOURCE_DIR}/server/src/udp_server_destroy.c
    ${CMAKE_SOURCE_DIR}/server/src/udp_server_has_client.c
    ${CMAKE_SOURCE_DIR}/server/src/udp_server_rm_client.c
    ${CMAKE_SOURCE_DIR}/server/main.c
)

add_executable(client ${client_sources})
add_executable(server ${server_sources})

target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/client/include)
target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/server/include)
