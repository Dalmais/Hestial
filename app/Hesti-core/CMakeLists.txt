cmake_minimum_required(VERSION 3.16)

project(Homebase CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRCS 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    )

add_executable(Homebase ${SRCS})
