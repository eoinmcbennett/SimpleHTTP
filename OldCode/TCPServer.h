//
// Created by Eoin on 12/07/2020.
//

#ifndef SERVERTEST_TCPSERVER_H
#define SERVERTEST_TCPSERVER_H

#include <iostream>
#include "client.h"
#include "Util.h"
#include <queue>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>

#define DEFAULT_PORT 5050
#define TIMEOUT 220

struct TCPClient{
    uint16_t client_fd;
    std::time_t timeOfLastMessage;
};

class TCPServer {
    //Instance variables
private:
    std::vector<TCPClient> clients;
    //Server socket fd
    int server_socket_fd;

    //Maximum fd needed for select
    int maxFD;

    //The servers address and address length
    struct sockaddr_in server_address;
    int addr_len;

    //No of clients connected and their details
    unsigned char noOfClients;
    struct sockaddr_storage client_addresses;


    fd_set masterfds;
    fd_set tempfds;

    //Private set up functions
protected:
    std::queue<char*> messages;

    static char* allocateString(unsigned int size);

private:
    void bindSocket();
    void listenForIncoming();
    void handleNewIncoming();

    void receive(uint16_t fd);

    static TCPClient* allocateClient();
    void freeClient(TCPClient* client);

    void checkForDeadClients();

    //Public functions
public:

    TCPServer();
    TCPServer(u_int16_t port);

    ~TCPServer();

    int init(uint16_t port);

    virtual void loop();
    void shutDown();

    virtual void onMessageReceived(uint16_t fd, char* message);

    u_int16_t sendMessage(u_int16_t sock_fd, const char* message);
    u_int16_t sendMessage(u_int16_t sock_fd, char* message);

    void (*newConnectionCallback)(u_int16_t sock_fd);
    void (*receiveCallback)(u_int16_t sock_fd, char* buffer);
    void (*disconnectCallback)(u_int16_t sock_fd);


};


#endif //SERVERTEST_TCPSERVER_H
