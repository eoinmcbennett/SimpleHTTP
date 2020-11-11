//
// Created by Eoin on 21/08/2020.
//

#include "HTTPServer.h"
#include "Responses.h"

HTTPServer::HTTPServer(unsigned short port, const std::string& site_path, const std::string& default_404_page_path,uint8_t no_of_threads){
    this->running = true;
    this->server_socket = new HTTPServerSocket(port);
    //this->thread_pool = new ThreadPool(no_of_threads);
    this->site_path = site_path;
    this->default_404_page_path = default_404_page_path;

    //Thread initialisation
    this->connectionListener = new std::thread(&HTTPServer::listenForSocket, this);
    this->requestListener = new std::thread(&HTTPServer::listenForRequests,this);
    this->requestHandler = new std::thread(&HTTPServer::handleRequest, this);
    this->responseSender = new std::thread(&HTTPServer::sendResponse,this);
}

/**
 * Listens for incoming connections on the server port
 */
void HTTPServer::listenForSocket() {
    while(running){
        HTTPConnection* connection = server_socket->AcceptConnection();
        if(connection != nullptr){
            std::cout << "Accepting new connection!" << std::endl;
            std::cout << connection->getConnDetails() << std::endl;
            persistent_connections.emplace_back(connection);
        }
    }
}

/**
 * Checks each client for a new request puts its on the queue for processing
 */
void HTTPServer::listenForRequests() {
    while(running){
        for(int i = 0; i < persistent_connections.size(); i++){
            Request* request = persistent_connections.at(i)->getRequest();
            requests.enqueueData(request);
        }
    }
}

/**
 * Handles the next request in line on the queue
 */
void HTTPServer::handleRequest(){
    while(running){
        if(!requests.isEmpty()){
            Request* request = this->requests.dequeue();
            Response* response = new Response;
            memset(response,0,sizeof(Response));

            bool handled;
            switch(request->method){
                case GET  : handled = handleGetRequest(request,response); break;
                case HEAD : generate501Response(response); handled = true; break;
                default: generate404Response(response);  handled = true; break;
            }
            if(handled) {
                response->recipient = request->sender;
                delete request;
                responses.enqueueData(response);
            } else {
                std::cout << "Failed to handle request!" << std::endl;
                std::cout << "Sender:" << std::endl << request->sender->getConnDetails() << std::endl;
            }
        }
    }
}

/**
 * Handles sending the completed responses
 */
void HTTPServer::sendResponse() {
    while(running){
        if(!responses.isEmpty()){
            Response* response = this->responses.dequeue();
            if(response){
                response->recipient->sendResponse(response);
                delete response;
            }
        }
    }
}

//RESPONSE HANDLING METHODS
bool HTTPServer::handleGetRequest(Request*& request, Response*& response) const {
    if(request == nullptr || response == nullptr){
        return false;
    }
    response->version = new char[strlen(request->version)];

    FILE* resource;
    //Create the path to the resource
    std::string resourcePath = site_path;
    if(memcmp(request->URL,"/",strlen(request->URL)) == 0){
        resourcePath.append("index.html");
    } else {
        resourcePath.append(request->URL);
    }
    //Open the resource
    resource = fopen(resourcePath.c_str(),"r");

    //If the resource was opened ok then read it, otherwise send 404
    if(resource){
        response->status = OK;
        response->statusCode = "200";
    } else {
        delete response;
        response = new Response;
        generate404Response(response);
        return true;
    }

    char* buf = (char*)malloc(250);
    unsigned long fileLength = 0;
    if(buf) {
        char ch = fgetc(resource);
        while(ch != EOF){
            buf[fileLength] = ch;
            fileLength++;
            ch = fgetc(resource);
        }
    }
    response->body = buf;

    //Handle headers
    Header* h1 = new Header("Content-Length",std::to_string(fileLength));
    h1->next = new Header("Server","SimpleHTTP");
    h1->next->next = new Header("Content-Type","text/html; charset = UTF-8");
    std::time_t now = std::time(nullptr);
    h1->next->next->next = new Header("Date",ctime(&now));
    response->headers = h1;

    return response;
}

Response *HTTPServer::handleUnsupported(Request *request) const {
    return nullptr;
}


void HTTPServer::setSitePath(std::string &site_path) {
    this->site_path = site_path;
}

std::string HTTPServer::getSitePath() const {
    return this->site_path;
}






