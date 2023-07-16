cmake_minimum_required(VERSION 3.10)

project(Homegarden CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(Homegarden PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB SOURCE CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable(Homegarden ${SOURCE})

install(TARGETS Homegarden
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
