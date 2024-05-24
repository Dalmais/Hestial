#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "socket.h"

class TCPSocket : public Socket {
public:
    TCPSocket();
    ~TCPSocket();

    bool bind(int port) override;
    bool send(const char* data, int length) override;
    bool receive(char* buffer, int length) override;
};

#endif // TCP_SOCKET_H
