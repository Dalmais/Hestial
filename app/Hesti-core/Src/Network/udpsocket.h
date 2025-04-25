#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "socket.h"

class UDPSocket : public Socket {
public:
    UDPSocket();
    ~UDPSocket();

    bool bind(int port) override;
    bool send(const char* data, int length) override;
    bool receive(char* buffer, int length) override;
};

#endif // UDP_SOCKET_H
