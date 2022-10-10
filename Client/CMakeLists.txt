cmake_minimum_required(VERSION 3.23)
project(Client)

set(CMAKE_CXX_STANDARD 17)
set(GLEW_STATIC ON)


set(ENET_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/enet-1.3.17/include/")

set(ENET_INCLUDE_FILES
        ${ENET_INCLUDE_DIR}/enet/callbacks.h
        ${ENET_INCLUDE_DIR}/enet/enet.h
        ${ENET_INCLUDE_DIR}/enet/list.h
        ${ENET_INCLUDE_DIR}/enet/protocol.h
        ${ENET_INCLUDE_DIR}/enet/time.h
        ${ENET_INCLUDE_DIR}/enet/types.h
        ${ENET_INCLUDE_DIR}/enet/unix.h
        ${ENET_INCLUDE_DIR}/enet/utility.h
        ${ENET_INCLUDE_DIR}/enet/win32.h
        )


set(ENET_LIB_DIR "${CMAKE_SOURCE_DIR}/libs/enet-1.3.17/")
set(ENET_SOURCE_FILES
        ${ENET_LIB_DIR}/callbacks.c
        ${ENET_LIB_DIR}/compress.c
        ${ENET_LIB_DIR}/host.c
        ${ENET_LIB_DIR}/list.c
        ${ENET_LIB_DIR}/packet.c
        ${ENET_LIB_DIR}/peer.c
        ${ENET_LIB_DIR}/protocol.c
        ${ENET_LIB_DIR}/unix.c
        ${ENET_LIB_DIR}/win32.c)

source_group(include FILES ${INCLUDE_FILES})
source_group(source FILES ${SOURCE_FILES})

add_library(enet STATIC
        ${ENET_INCLUDE_FILES}
        ${ENET_SOURCE_FILES}
        )

include_directories(${ENET_INCLUDE_DIR})
add_executable(Client main.cpp)

target_link_libraries(Client enet winmm ws2_32)
