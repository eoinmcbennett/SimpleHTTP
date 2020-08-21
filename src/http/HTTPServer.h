//
// Created by Eoin on 21/08/2020.
//

#ifndef SERVERTEST_HTTPSERVER_H
#define SERVERTEST_HTTPSERVER_H

#include "../net/HTTPServerSocket.h"
#include "../threading/ThreadPool.h"

class HTTPServer {
private:
    HTTPServerSocket server_socket;
    ThreadPool threadPool;
};


#endif //SERVERTEST_HTTPSERVER_H
