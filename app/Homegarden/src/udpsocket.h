#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "Socket.h"

class UDPSocket : public Socket {
public:
    UDPSocket();
    ~UDPSocket();

    bool create() override;
    bool bind(int port) override;
    bool send(const char* data, int length) override;
    bool receive(char* buffer, int length) override;
    void close() override;

private:
    int socket_fd;
};

#endif // UDP_SOCKET_H
