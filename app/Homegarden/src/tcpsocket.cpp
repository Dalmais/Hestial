#include "tcpsocket.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

TCPSocket::TCPSocket() : Socket(){}

TCPSocket::~TCPSocket() {
    close();
}

bool TCPSocket::bind(int port) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    if (::bind(m_socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        return false;
    }

    return true;
}

bool TCPSocket::send(const char* data, int length) {
    if (m_socket_fd == -1) {
        return false;
    }

    if((m_targetIp == 0) || (m_targetPort == 0)){
        return false;
    }

    int sent_bytes = write(m_socket_fd, data, length);

    return (sent_bytes == length);
}

bool TCPSocket::receive(char* buffer, int length) {
    if (m_socket_fd == -1) {
        return false;
    }

    int received_bytes = recv(m_socket_fd, buffer, length, 0);

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
