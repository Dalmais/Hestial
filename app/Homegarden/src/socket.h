#ifndef SOCKET_H
#define SOCKET_H

class Socket {
public:
    Socket(){}
    virtual ~Socket(){}

    virtual bool create() = 0;
    virtual bool bind(int port) = 0;
    virtual bool send(const char* data, int length) = 0;
    virtual bool receive(char* buffer, int length) = 0;
    virtual void close() = 0;
};

#endif // SOCKET_H
