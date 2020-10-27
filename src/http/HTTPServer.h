//
// Created by Eoin on 21/08/2020.
//

#ifndef SERVERTEST_HTTPSERVER_H
#define SERVERTEST_HTTPSERVER_H

#include <map>

#include "HTTPServerSocket.h"
#include "../threading/ThreadPool.h"
#include "../websocket/WebsocketHandler.h"


class HTTPServer {
private:
    HTTPServerSocket* server_socket;
    std::vector<HTTPConnection*> persistent_connections;

    ThreadPool* thread_pool;

    //Handler for websocket connections. If null web sockets are unsupported by the server instance
    WebsocketHandler* ws_handler;

    //Paths to needed files
    std::string site_path;
    std::string default_404_page_path;

    bool running = false;

    std::thread* listenerThread;
    std::thread* senderThread;


    std::queue<Request*> requests;
    std::vector<Response*> responses;



public:
    HTTPServer(unsigned short port, const std::string& site_path, const std::string& default_404_page_path, uint8_t no_of_threads);

    void setSitePath(std::string& site_path);
    std::string getSitePath() const;
    void listenForSocket();

private:
    void sendResponse(HTTPConnection& client, Response* response) const;

    void handleGetRequest(Request* request) const;

    void handleUnsupported(Request* request) const;
};


#endif //SERVERTEST_HTTPSERVER_H
