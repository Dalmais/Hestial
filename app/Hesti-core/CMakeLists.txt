cmake_minimum_required(VERSION 3.16)

project(hesticore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRCS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Log/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Network/udpsocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Network/tcpsocket.cpp
)

add_library(hesticore ${SRCS})

target_include_directories(hesticore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
