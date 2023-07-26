cmake_minimum_required(VERSION 3.10)

project(Homegarden CXX)

set(CMAKE_CXX_STANDARD 17)
include(CTest)

set(SRCS 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    )

add_executable(Homegarden ${SRCS})
