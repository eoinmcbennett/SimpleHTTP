//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_HTTPSERVERSOCKET_H
#define SERVERTEST_HTTPSERVERSOCKET_H

#include "../net/ServerSocket.h"
#include "HTTPConnection.h"

class HTTPServerSocket: public ServerSocket {
public:
    explicit HTTPServerSocket(unsigned short port);
    HTTPConnection* AcceptConnection() override;
};


#endif //SERVERTEST_HTTPSERVERSOCKET_H
