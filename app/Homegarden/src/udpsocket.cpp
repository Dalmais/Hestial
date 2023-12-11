#include "UDPSocket.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

UDPSocket::UDPSocket() : socket_fd(-1) {}

UDPSocket::~UDPSocket() {
    close();
}

bool UDPSocket::create() {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    return (socket_fd != -1);
}

bool UDPSocket::bind(int port) {
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

bool UDPSocket::send(const char* data, int length) {
    // Implement sending data via UDP socket
    // Use sendto() function
    return false;
}

bool UDPSocket::receive(char* buffer, int length) {
    // Implement receiving data via UDP socket
    // Use recvfrom() function
    return false;
}

void UDPSocket::close() {
    if (socket_fd != -1) {
        ::close(socket_fd);
        socket_fd = -1;
    }
}
