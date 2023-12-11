#include "udpsocket.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

UDPSocket::UDPSocket() : Socket(), socket_fd(-1) {}

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
    if (socket_fd == -1) {
        return false;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(tcpHost.c_str()); // Replace with the actual destination IP
    server_address.sin_port = htons(tcpPort);

    int sent_bytes = sendto(socket_fd, data, length, 0, (struct sockaddr*)&server_address, sizeof(server_address));

    return (sent_bytes == length);
}

bool UDPSocket::receive(char* buffer, int length) {
    if (socket_fd == -1) {
        return false;
    }

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    memset(&client_address, 0, client_address_len);

    int received_bytes = recvfrom(socket_fd, buffer, length, 0, (struct sockaddr*)&client_address, &client_address_len);

    if (received_bytes > 0) {
        // You can optionally print the client's IP and port:
        // std::cout << "Received from " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << std::endl;
        return true;
    } else {
        return false;
    }
}

void UDPSocket::close() {
    if (socket_fd != -1) {
        ::close(socket_fd);
        socket_fd = -1;
    }
}
