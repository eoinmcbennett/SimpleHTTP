//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_SOCKET_H
#define SERVERTEST_SOCKET_H


#include <netinet/in.h>
#include <iostream>

class Socket {
private:
    int sock_FD;

protected:
    void createSocket();
    void closeSocket();
public:
    virtual void init();
    Socket();
    explicit Socket(int sock_FD);
};


#endif //SERVERTEST_SOCKET_H
