//
// Created by Eoin on 22/08/2020.
//

#include <cstring>
#include "HTTPConnection.h"
#include "Response.h"

HTTPConnection::HTTPConnection(Socket socket) : Connection(socket) {

}

/**
 * Sends the response to the client that this connection represents
 * @param response
 */
void HTTPConnection::sendResponse(Response * response) {
    if(response != nullptr){
        std::string res = Response::convertResponseToString(response);
        send(this->conn_socket.getSockFD(),res.c_str(),strlen(res.c_str()),0);
    }
}

/**
 * Gets any request sent to the connection
 * @return
 */
Request *HTTPConnection::getRequest() {

}
