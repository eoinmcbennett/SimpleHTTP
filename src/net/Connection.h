//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_CONNECTION_H
#define SERVERTEST_CONNECTION_H

#include <chrono>

#include "Socket.h"

//Forward Declarations for Response and request
class Response;
class Request;

class Connection {
private:
    Socket conn_socket;
    time_t timeOfLastMessage;

    void operator()(Socket conn_socket);

public:
    virtual void sendResponse(Response*) = 0;
    virtual Request* receiveRequest() = 0;
};


#endif //SERVERTEST_CONNECTION_H
