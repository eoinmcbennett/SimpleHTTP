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
    close(sock_FD);
}

Socket::Socket(int sock_FD) {
    this->sock_FD = sock_FD;
}

Socket::Socket() {

}

void Socket::init() {

}
