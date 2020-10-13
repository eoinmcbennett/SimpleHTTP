//
// Created by Eoin on 21/08/2020.
//

#include "HTTPServer.h"

HTTPServer::HTTPServer(unsigned short port, std::string& site_path, std::string& default_404_page_path,uint8_t no_of_threads){
    this->server_socket = new HTTPServerSocket(port);
    //this->thread_pool = new ThreadPool(no_of_threads);
    this->site_path = site_path;
    this->default_404_page_path = default_404_page_path;
}

void HTTPServer::listenForSocket() {
    HTTPConnection* connection = server_socket->AcceptConnection();
    if(connection != nullptr){
        std::cout << connection->getConnDetails() << std::endl;
        Request* request = connection->getRequest();
        requests.push(request);
    }
}

void HTTPServer::setSitePath(std::string &site_path) {
    this->site_path = site_path;
}

std::string HTTPServer::getSitePath() {
    return this->site_path;
}

void HTTPServer::sendResponse(HTTPConnection &client, Response *response) {

}
