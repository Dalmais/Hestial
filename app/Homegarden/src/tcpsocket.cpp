#include "tcpsocket.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

TCPSocket::TCPSocket() : Socket(), socket_fd(-1) {}

TCPSocket::~TCPSocket() {
    close();
}

bool TCPSocket::create() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    return (socket_fd != -1);
}

bool TCPSocket::bind(int port) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    if (::bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        return false;
    }

    return true;
}

bool TCPSocket::send(const char* data, int length) {
    if (socket_fd == -1) {
        return false;
    }

    int sent_bytes = send(socket_fd, data, length, 0);

    return (sent_bytes == length);
}

bool TCPSocket::receive(char* buffer, int length) {
    if (socket_fd == -1) {
        return false;
    }

    int received_bytes = recv(socket_fd, buffer, length, 0);

    if (received_bytes > 0) {
        return true;
    } else if (received_bytes == 0) {
        // Connection closed by the remote side
        return false;
    } else {
        // Handle error (received_bytes == -1)
        return false;
    }
}

void TCPSocket::close() {
    if (socket_fd != -1) {
        ::close(socket_fd);
        socket_fd = -1;
    }
}
