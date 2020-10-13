//
// Created by Eoin on 15/08/2020.
//

#include "HTTPServerSocket.h"

/**
 * Attempts to accept a HTTP Connection on the server socket
 * @return
 */
HTTPConnection* HTTPServerSocket::AcceptConnection() {
    //Accept and fill out the incoming clients details
    sockaddr_in* socket_addr = new sockaddr_in;
    size_t* addr_len = new size_t;
    *addr_len = sizeof(socket_addr);
    int sock_fd = accept(this->sock_FD, (sockaddr *)socket_addr, addr_len);

    //Check for error condition
    if(sock_fd > 0){
        Socket* p_socket = new Socket(sock_fd, *socket_addr, *addr_len);
        return new HTTPConnection(p_socket);
    }
    perror("Failed to accept connection on socket: ");
    return nullptr;
}

/**
 * Default constructor for a http server socket
 * Handles all initialisation of the socket
 * @param port
 */
HTTPServerSocket::HTTPServerSocket(unsigned short port) : ServerSocket(port) { }
