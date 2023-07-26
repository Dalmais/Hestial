cmake_minimum_required(VERSION 3.16)

project(Homegarden CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()


set(SRCS 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    )

add_executable(Homegarden ${SRCS})

if(BUILD_TESTING)

    include(GoogleTest)
    gtest_discover_tests(Homegarden)
endif()
