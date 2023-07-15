cmake_minimum_required(VERSION 3.5)

project(Homegarden LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE
     "*.h"
     "*.cpp"
)

add_executable(Homegarden ${SOURCE})

install(TARGETS Homegarden
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
