//
// Created by Eoin on 30/07/2020.
//

#ifndef SERVERTEST_HTTPSERVER_H
#define SERVERTEST_HTTPSERVER_H

#include "../TCP/TCPServer.h"
#include "HTTPClient.h"
#include "Response.h"
#include "Request.h"

#include <vector>
#include <thread>

class HTTPServer: public TCPServer {
private:
    std::vector<std::thread> clientThreads;
    const char* sitePath;

public:
    HTTPServer(unsigned short port, unsigned int maxClients = 256, unsigned int clientTimeoutTime = 600,const char* sitePath = "/");
    ~HTTPServer();

    void loop() override;

    void handleRequest(HTTPClient* sender, Request* request);

    std::vector<std::thread> getClientThreads();

private:
    HTTPClient* checkForNewClients() override;

    static void clientThreadRunner(HTTPClient* client);

    Response *handleGetRequest(Request *pRequest);

    Response *handlePostRequest(Request *pRequest);

    Response *handleUnsupportedRequest(Request *pRequest);
};

#endif //SERVERTEST_HTTPSERVER_H
