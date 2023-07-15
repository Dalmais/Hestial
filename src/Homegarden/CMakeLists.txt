cmake_minimum_required(VERSION 3.5)

project(Homegarden LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_directory({CMAKE_CURRENT_SOURCE_DIR} SUB_SOURCES)

add_executable(Homegarden main.cpp)

install(TARGETS Homegarden
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
