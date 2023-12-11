
set(SRCS 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/commands.cpp
    ${PROJECT_SOURCE_DIR}/src/logger.cpp
    ${PROJECT_SOURCE_DIR}/src/socket.cpp
    ${PROJECT_SOURCE_DIR}/src/udpsocket.cpp
    ${PROJECT_SOURCE_DIR}/src/tcpsocket.cpp
    ${PROJECT_SOURCE_DIR}/src/commandsparser.cpp
    )

add_executable(Homegarden ${SRCS})
