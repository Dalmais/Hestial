cmake_minimum_required(VERSION 3.10)

project(Homegarden CXX)

set(CMAKE_CXX_STANDARD 17)
set(SRCS 
    main.cpp
    )

add_executable(Homegarden ${SRCS})
