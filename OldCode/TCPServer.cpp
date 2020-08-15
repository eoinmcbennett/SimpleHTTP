//
// Created by Eoin on 12/07/2020.
//

#include <strings.h>
#include <cstring>
#include "TCPServer.h"
#include "TCP/TCPServer.h"


TCPServer::TCPServer() {
    init(DEFAULT_PORT);
}

TCPServer::TCPServer(u_int16_t port) {
    init(port);
}

TCPServer::~TCPServer() {
    close(server_socket_fd);

}


int TCPServer::init(uint16_t port) {

    server_socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket_fd < 0){
        perror("Failed to create server socket: ");
        return -1;
    }

    FD_ZERO(&masterfds);
    FD_ZERO(&tempfds);


    addr_len = sizeof(server_address);
    bzero(&server_address,addr_len);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(port);

    newConnectionCallback = nullptr;
    receiveCallback = nullptr;
    disconnectCallback = nullptr;

    bindSocket();
    listenForIncoming();

    return 0;
}

void TCPServer::bindSocket() {
    std::cout << "Binding server socket" << std::endl;

    int bind_res = bind(server_socket_fd, (struct sockaddr *) &server_address, addr_len);

    if(bind_res < 0){
        perror("Failed to bind server socket: ");
        return;
    }

    FD_SET(server_socket_fd,&masterfds);
    maxFD = server_socket_fd;
}

void TCPServer::listenForIncoming() {
    std::cout << "Attempting to start listening" << std::endl;

    int listen_res = listen(server_socket_fd,4);

    if(listen_res < 0){
        perror("Listen failed: ");
        return;
    }
}

void TCPServer::handleNewIncoming() {
    socklen_t clientAddrLen = sizeof(client_addresses);

    int temp_fd = accept(server_socket_fd,(struct sockaddr*)&client_addresses,&clientAddrLen);

    if(temp_fd < 0){
        perror("Failed to accept incoming connection! ");
        return;
    }

    //Check for existing client
    for(int i = 0; i < clients.size(); i++){
        if(temp_fd == clients.at(i).client_fd){
            std::cout << "Tried to process new connection from existing client" << std::endl;
            return;
        }
    }

    FD_SET(temp_fd,&masterfds);

    if(temp_fd > maxFD){
        maxFD = temp_fd;
    }

    std::cout << "New client successfully connected" << std::endl;
    TCPClient* client = allocateClient();
    client->client_fd = temp_fd;
    client->timeOfLastMessage = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    clients.push_back(*client);
    noOfClients++;

    if(newConnectionCallback != nullptr){
        newConnectionCallback(temp_fd);
    }
}

void TCPServer::loop() {
    tempfds = masterfds; //FD copy

    int sel = select(maxFD + 1, &tempfds, NULL, NULL, NULL);

    if(sel < 0){
        std::cout << "Call to select failed" << std::endl;
        shutDown();
        return;
    }

    for(int i = 0; i <= maxFD; i++){
        if(FD_ISSET(i,&tempfds) > 0){
            //New connection
            if(server_socket_fd == i)
                handleNewIncoming();
            //Receive data from an existing connection
            else
                receive(i);
        }
    }

    //Check for dead clients
    checkForDeadClients();
}



void TCPServer::receive(uint16_t fd) {

    char* data = allocateString(1024);
    int no_bytesReceived = recv(fd,data,1024,MSG_PEEK);

    //A problem occurred
    if(no_bytesReceived <= 0){
        //Dead client
        if(no_bytesReceived == 0){
        }
        else {
            perror("Receive from client failed: ");
        }
    }
    else{
        //Change the time of the clients last message to now
        for(int i = 0; i < clients.size(); i++){
            if(clients.at(i).client_fd == fd)
                clients.at(i).timeOfLastMessage = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }

        std::cout << "Received: " << data << std::endl;
        onMessageReceived(fd,data);
       // messages.push(data);
       free(data);
    }
}

void TCPServer::shutDown() {
    close(server_socket_fd);
    std::cout << "Server connection closed" << std::endl;
}

u_int16_t TCPServer::sendMessage(u_int16_t sock_fd, char *message) {
    return send(sock_fd,message,strlen(message),0);
}

u_int16_t TCPServer::sendMessage(u_int16_t sock_fd, const char *message) {
    return send(sock_fd,message,strlen(message),0);
}

void TCPServer::onMessageReceived(uint16_t fd, char *message) {

}




/**
 * Returns a pointer to a location with size amount of bytes allocated
 * Automatically adds a null terminator
 * @param size
 * @return
 */
char* TCPServer::allocateString(unsigned int size){
    char* mem = (char*)malloc(size + 1);
    if(!mem){
        return nullptr;
    }
    bzero(mem,size);
    mem[size] = '\0';
    return mem;
}

TCPClient *TCPServer::allocateClient() {
    TCPClient* client = (TCPClient*)malloc(sizeof(TCPClient));
    bzero(client,sizeof(TCPClient));
    return client;
}

void TCPServer::freeClient(TCPClient* client) {
    free(client);
}

/**
 * Checks for clients that have not sent data recently
 */
void TCPServer::checkForDeadClients() {
    for(int i = 0; i < clients.size(); i++){

    }
}

