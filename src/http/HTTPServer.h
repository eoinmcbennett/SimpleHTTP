//
// Created by Eoin on 21/08/2020.
//

#ifndef SERVERTEST_HTTPSERVER_H
#define SERVERTEST_HTTPSERVER_H

#include "../util/Queue.h"

#include "HTTPServerSocket.h"
#include "../threading/ThreadPool.h"
#include "../websocket/WebsocketHandler.h"
#include "Request.h"
#include "Response.h"

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

    std::thread* connectionListener;
    std::thread* requestListener;
    std::thread* requestHandler;
    std::thread* responseSender;


    Queue<Request*> requests;
    Queue<Response*> responses;



public:
    HTTPServer(unsigned short port, const std::string& site_path, const std::string& default_404_page_path, uint8_t no_of_threads);

    void setSitePath(std::string& site_path);

    std::string getSitePath() const;
    std::string getDefault404Path() const;
    WebsocketHandler* getWebsocketHandler() const;


private:
    void listenForSocket();
    void listenForRequests();
    void handleRequest();
    void sendResponse();

    bool handleGetRequest(Request*& request, Response*& response) const;
    bool handleUnsupported(Request*& request, Response*& response) const;

};


#endif //SERVERTEST_HTTPSERVER_H
