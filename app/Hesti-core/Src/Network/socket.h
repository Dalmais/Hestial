#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

class Socket {
public:

    static const int32_t NO_FD = -1;

    Socket(const uint32_t targetIp = 0, const uint16_t targetPort = 0) : 
        m_socket_fd(NO_FD), m_targetIp(targetIp), m_targetPort(targetPort){}
    Socket(const std::string & targetIp, const uint16_t targetPort) : 
        m_socket_fd(NO_FD), m_targetIp(inet_addr(targetIp.c_str())), m_targetPort(targetPort){}
    virtual ~Socket(){}

    virtual bool create() {
        m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        return (m_socket_fd != -1);
    }

    virtual bool bind(int port) = 0;
    virtual bool send(const char* data, int length) = 0;
    virtual bool receive(char* buffer, int length) = 0;

    void close() {
        if (m_socket_fd != -1) {
            ::close(m_socket_fd);
            m_socket_fd = -1;
        }
    }

protected:
    int32_t m_socket_fd;
    uint32_t m_targetIp;
    uint16_t m_targetPort;
};

#endif // SOCKET_H
