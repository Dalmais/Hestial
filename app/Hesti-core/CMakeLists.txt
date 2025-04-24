cmake_minimum_required(VERSION 3.16)

project(hestiacore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRCS 
    ${PROJECT_SOURCE_DIR}/Src/Log/main.cpp
)

target_include_directories(hesti-core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(hestiacore ${SRCS})
