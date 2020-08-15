//
// Created by Eoin on 25/07/2020.
//

#ifndef SERVERTEST_TCPCLIENT_H
#define SERVERTEST_TCPCLIENT_H

#include <iostream>
#include <chrono>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>



/**
 *  * This class should only be instantiated by TCPServer, any instance of this class made outside will not be a live tcp client
 * Defines a simple implementation of a tcp client
 * Should always be instantiated on a new thread due to the message checking functions blocking until a message is received
 * Default timeout is 10 minutes, custom timeout time can be set
 * Will return from its blocking function when client times out
 */
class TCPClient {
private:
    unsigned short sock_fd;
    sockaddr_in clientDetails;
    size_t addr_len;

    std::time_t timeOfLastMessage;
    unsigned int timeoutTimeInSeconds = 600;

public:
    explicit TCPClient(unsigned short sock_fd);
    TCPClient(unsigned short sock_fd,sockaddr_in client_addr, size_t addr_len, unsigned int timeoutTimeInSeconds);
    TCPClient(unsigned short sock_fd, unsigned int timeoutTimeInSeconds);

    ~TCPClient();

    int sendToClient(const char* data, unsigned int len);
    void setReceiveCallback(void(*func)(const char*));

    //Control function that poll for new messages
    virtual void loop();

    sockaddr_in getClientSockAddr();
    size_t getClientSockAddrLen();
    //Private member functions
private:




protected:
    bool isClientTimedOut();
    void closeConnection();
    const char* checkForNewMessage();
    void (*receiveCallback)(const char*);
};


#endif //SERVERTEST_TCPCLIENT_H
