#include "udpsocket.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

UDPSocket::UDPSocket() : Socket(){}

UDPSocket::~UDPSocket() {
    close();
}

bool UDPSocket::bind(int port) {
    if ((m_socket_fd == -1) && (create() == false)) {
        return false;
    }

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

bool UDPSocket::send(const char* data, int length) {
    if ((m_socket_fd == -1) && (create() == false)) {
        return false;
    }

    if((m_targetIp == 0) || (m_targetPort == 0)){
        return false;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = m_targetIp;
    server_address.sin_port = htons(m_targetPort);

    int sent_bytes = sendto(m_socket_fd, data, length, 0, (struct sockaddr*)&server_address, sizeof(server_address));

    return (sent_bytes == length);
}

bool UDPSocket::receive(char* buffer, int length) {
    if ((m_socket_fd == -1) && (create() == false)) {
        return false;
    }

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    memset(&client_address, 0, client_address_len);

    int received_bytes = recvfrom(m_socket_fd, buffer, length, 0, (struct sockaddr*)&client_address, &client_address_len);

    if (received_bytes > 0) {
        // You can optionally print the client's IP and port:
        // std::cout << "Received from " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << std::endl;
        return true;
    } else {
        return false;
    }
}
