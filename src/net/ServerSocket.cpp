//
// Created by Eoin on 15/08/2020.
//

#include "ServerSocket.h"

/**
 * Binds the socket to the machines IP and specified port number
 */
void ServerSocket::bindSocket(unsigned short port){
    addr_len = sizeof(server_address);
    bzero(&server_address,addr_len);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(port);

    int bind_res = bind(server_socket_fd, (struct sockaddr *) &server_address, addr_len);
    if(bind_res < 0){
        perror("Failed to bind server socket: ");
    }
}

/**
 * Sets the socket to listen
 */
void ServerSocket::listenSocket() {
    int listen_res = listen(server_socket_fd,4);
    if(listen_res < 0){
        perror("Listen failed: ");
    }
}

