cmake_minimum_required(VERSION 3.16)

project(Homegarden LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)