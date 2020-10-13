//
// Created by Eoin on 15/08/2020.
//


#include "ServerSocket.h"

/**
 * Binds the socket to the machines IP and specified port number
 */
void ServerSocket::bindSocket(unsigned short port){
    addr_len = sizeof(this->socket_addr);
    bzero(&this->socket_addr,addr_len);

    this->socket_addr.sin_family = AF_INET;
    this->socket_addr.sin_addr.s_addr = INADDR_ANY;
    this->socket_addr.sin_port = htons(port);

    int bind_res = bind(this->sock_FD, (struct sockaddr *) &this->socket_addr, addr_len);
    if(bind_res < 0){
        perror("Failed to bind server socket: ");
    }
}

/**
 * Sets the socket to listen
 */
void ServerSocket::listenSocket() {
    int listen_res = listen(this->sock_FD,1);
    if(listen_res < 0){
        perror("Listen failed: ");
    }
}

ServerSocket::ServerSocket(unsigned short port): Socket() {
    bindSocket(port);
    listenSocket();
}

