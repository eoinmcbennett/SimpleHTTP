//
// Created by Eoin on 29/07/2020.
//

#include "TCPServer.h"



TCPServer::TCPServer(unsigned short port, unsigned int maxClients, unsigned int clientTimeoutTime) {
    this->maxClients = maxClients;
    this->clientTimeoutTime = clientTimeoutTime;
    init(port);
}

TCPServer::~TCPServer() {
    close(server_fd);
}

void TCPServer::init(unsigned short port) {
    //Initialise the socket and check if its valid
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd < 0){
        perror("Failed to create server socket: ");
        return;
    }

    //Set the server address params;
    addr_len = sizeof(server_addr);
    bzero(&server_addr,addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);

    //Bind the socket and check for failure
    int bind_res = bind(server_fd, (struct sockaddr*)&server_addr, addr_len);
    if(bind_res < 0){
        perror("Failed to bind server socket: ");
        return;
    }

    //Mark the socket as accepting connections
    int listen_res = listen(server_fd,SOMAXCONN);
    if(listen_res < 0){
        perror("Failed to mark socket as listening: ");
        return;
    }
    //Successfully initialised the TCPServer!
}

void TCPServer::loop() {
    while(true){
        checkForNewClients();
    }
}

TCPClient* TCPServer::checkForNewClients() {
    sockaddr_in client_addr;
    size_t client_addr_len = 0;

    //Accept a new connection
    int temp_fd = accept(server_fd,(struct sockaddr*)&client_addr,&client_addr_len);



    //There was a successful connection
    if(temp_fd > 0){
        TCPClient* client = new TCPClient(temp_fd, client_addr, addr_len, clientTimeoutTime);
        clients.push_back(client);

        if(newClientCallback != nullptr){
            newClientCallback(client);
        }
        return client;
    }
    return nullptr;
}

void TCPServer::setNewConnectionCallback(void (*callback)(TCPClient *)) {
    newClientCallback = callback;
}

