//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_HTTPSERVERSOCKET_H
#define SERVERTEST_HTTPSERVERSOCKET_H

#include "ServerSocket.h"

class HTTPServerSocket: public ServerSocket {
public:
    void init() override;
    Connection* AcceptConnection() override;
};


#endif //SERVERTEST_HTTPSERVERSOCKET_H
