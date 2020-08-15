//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_SERVERSOCKET_H
#define SERVERTEST_SERVERSOCKET_H

#include "Socket.h"

class Connection;

class ServerSocket : public Socket {
private:
    sockaddr_in server_addr;
    size_t addr_len;

protected:
    void bindSocket(unsigned short port);
    void listenSocket();

public:
    virtual Connection* AcceptConnection() = 0;
};


#endif //SERVERTEST_SERVERSOCKET_H
