//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_SERVERSOCKET_H
#define SERVERTEST_SERVERSOCKET_H

#include <strings.h>

#include "Socket.h"

class Connection;

/**
 * Represents a Servers Socket within the program
 */
class ServerSocket : public Socket {
protected:
    void bindSocket(unsigned short port);
    void listenSocket();

    explicit ServerSocket(unsigned short port);

public:
    virtual Connection* AcceptConnection() = 0;
};


#endif //SERVERTEST_SERVERSOCKET_H
