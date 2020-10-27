//
// Created by Eoin on 22/08/2020.
//

#include <cstring>
#include <errno.h>

#include "HTTPConnection.h"
#include "Response.h"
#include "Request.h"

HTTPConnection::HTTPConnection(Socket* socket) : Connection(socket) {

}

/**
 * Sends the response to the client that this connection represents
 * @param response
 */
void HTTPConnection::sendResponse(Response * response) {
    if(response != nullptr){
        std::string res = Response::convertResponseToString(response);
        send(this->conn_socket->getSockFD(),res.c_str(),strlen(res.c_str()),0);
    }
}

/**
 * Gets any request sent to the connection
 * @return
 */
Request* HTTPConnection::getRequest() {
    char* recv_buf = new char[5000];
    int bytesRec = recv(this->conn_socket->getSockFD(),recv_buf,5000,0);

    if(bytesRec < 0){
        delete[] recv_buf;
        perror("recv() error: ");
        fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
        return nullptr;
    }

    if(bytesRec < 5000 && bytesRec > 0){
        if(bytesRec == 0){
            delete[] recv_buf;
            return nullptr;
        }
        char* temp = new char[bytesRec];
        memcpy(temp,recv_buf,bytesRec);
        delete[] recv_buf;
        recv_buf = temp;
    }

    Request* req = Request::getRequestFromRawString(recv_buf);
    req->sender = this;
    delete[] recv_buf;
    return req;
}
