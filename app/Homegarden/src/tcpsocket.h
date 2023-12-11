#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "Socket.h"

class TCPSocket : public Socket {
public:
    TCPSocket();
    ~TCPSocket();

    bool create() override;
    bool bind(int port) override;
    bool send(const char* data, int length) override;
    bool receive(char* buffer, int length) override;
    void close() override;

private:
    int socket_fd;
};

#endif // TCP_SOCKET_H
