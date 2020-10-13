//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_SOCKET_H
#define SERVERTEST_SOCKET_H


#include <netinet/in.h>
#include <iostream>

class Socket {
protected:
    int sock_FD;
    sockaddr_in socket_addr;
    size_t addr_len;

    void createSocket();
    void closeSocket();
private:
    bool wasCreatedExternally;
public:

    explicit Socket();
    ~Socket();
    explicit Socket(int sock_FD);
    Socket(int sock_FD,sockaddr_in socket_addr, size_t addr_len);

    sockaddr_in getSocketAddr();
    int getSockFD();
    size_t getAddrLen();

};


#endif //SERVERTEST_SOCKET_H
