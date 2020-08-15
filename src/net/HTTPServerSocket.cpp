//
// Created by Eoin on 15/08/2020.
//

#include "HTTPServerSocket.h"


void HTTPServerSocket::init() {
    createSocket();
    bindSocket(5050);
    listenSocket();
}

HTTPConnection* HTTPServerSocket::AcceptConnection() {

}
