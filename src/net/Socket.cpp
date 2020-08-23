//
// Created by Eoin on 15/08/2020.
//

#include <zconf.h>
#include "Socket.h"

void Socket::createSocket() {
    sock_FD = socket(AF_INET,SOCK_STREAM,0);
    if(sock_FD < 0){
        perror("Failed to create socket: ");
    }
}

void Socket::closeSocket() {
    close(this->sock_FD);
}

Socket::Socket(int sock_FD) {
    this->sock_FD = sock_FD;
}

Socket::Socket() {
    createSocket();
}


Socket::~Socket() {
    closeSocket();
}

Socket::Socket(int sock_FD, sockaddr_in socket_addr, size_t addr_len) {
    this->sock_FD = sock_FD;
    this->socket_addr = socket_addr;
    this->addr_len = addr_len;
}

sockaddr_in Socket::getSocketAddr() {
    return this->socket_addr;
}

int Socket::getSockFD() {
    return this->sock_FD;
}

size_t Socket::getAddrLen() {
    return this->addr_len;
}
