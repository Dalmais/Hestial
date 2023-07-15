cmake_minimum_required(VERSION 3.5)

project(Homegarden LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory({CMAKE_CURRENT_SOURCE_DIR} SUB_SOURCES)

set(SOURCE
  ${SOURCE}
  ${SUB_SOURCES}
  PARENT_SCOPE
)

add_executable(Homegarden ${SOURCE})

install(TARGETS Homegarden
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
