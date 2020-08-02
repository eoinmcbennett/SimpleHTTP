//
// Created by Eoin on 29/07/2020.
//

#ifndef SERVERTEST_TCPSERVER_H
#define SERVERTEST_TCPSERVER_H

#include "TCPClient.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

/**
 * This class acts as a TCP server for clients to connect to
 * Clients are instantiated and placed into the clients vector
 * Applications that wish to listen to clients should assign a function to the clients callback
 * and then call loop on a new thread
 *
 * By default this server will allow up to 256 concurrent clients
 * Change this by calling TCPServer(port,maxClients)
 */
class TCPServer {
private:
    std::vector<TCPClient*> clients;

    unsigned short server_fd;
    sockaddr_in server_addr;
    size_t addr_len;
    unsigned int maxClients = 256;
    unsigned int clientTimeoutTime = 600;

    //Callback for when a new client is connected to the server
    void(*newClientCallback)(TCPClient* client);

public:
    TCPServer(unsigned short port, unsigned int maxClients= 256,unsigned int clientTimeoutTime= 600);

    ~TCPServer();

    virtual void loop();

    void setNewConnectionCallback(void(*callback)(TCPClient* client));

private:
    void init(unsigned short port);
protected:

    virtual TCPClient* checkForNewClients();

};


#endif //SERVERTEST_TCPSERVER_H
