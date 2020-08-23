//
// Created by Eoin on 22/08/2020.
//

#ifndef SERVERTEST_HTTPCONNECTION_H
#define SERVERTEST_HTTPCONNECTION_H

#include "../net/Connection.h"

class Response;
class Request;

class HTTPConnection : public Connection {
public:
    explicit HTTPConnection(Socket socket);

    void sendResponse(Response*);
    Request* getRequest();
};


#endif //SERVERTEST_HTTPCONNECTION_H
