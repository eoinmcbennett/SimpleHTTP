//
// Created by Eoin on 25/07/2020.
//

#include "TCPClient.h"

/**
 * Instantiates the client and records the socket number
 * Calls loop at the end of the constructor and will block as a result
 * Instantiate and construct this object on a new thread
 * @param sock_fd - The socket of the client
 */
TCPClient::TCPClient(uint16_t sock_fd) {
    sock_fd = sock_fd;
    timeOfLastMessage = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    loop();
}

/**
 * @param sock_fd Client socket
 * @param timeoutTimeInSeconds - seconds to wait before disconnecting the client
 */
TCPClient::TCPClient(unsigned short sock_fd, unsigned int timeoutTimeInSeconds) {
    this->sock_fd = sock_fd;
    if(timeoutTimeInSeconds == 0){
        return;
    }
    this->timeoutTimeInSeconds = timeoutTimeInSeconds;
}

TCPClient::TCPClient(unsigned short sock_fd, sockaddr_in client_addr,size_t addr_len ,unsigned int timeoutTimeInSeconds) {
    this->sock_fd = sock_fd;
    this->clientDetails = client_addr;
    this->addr_len = addr_len;
    if(timeoutTimeInSeconds == 0){
        return;
    }
    this->timeoutTimeInSeconds = timeoutTimeInSeconds;
}

//Ensure the socket is closed
TCPClient::~TCPClient() {
    close(sock_fd);
}

/**
 * Sends len bytes from the start of pointer data
 * @param data - The start of the message
 * @param len - The length of the message
 * @return
 */
int TCPClient::sendToClient(const char* data, unsigned int len) {
    //Check for valid input parameters
    if(data == nullptr || len == 0){
        //Ensure returned error code is outside the sendToClient error code range
        return -10000;
    }
    //Attempt to sendToClient the
    int res = send(sock_fd, data,len,0);
    return res;
}

/**
 * Sets the receive function callback
 * @param func
 */
void TCPClient::setReceiveCallback(void (*func)(const char *)) {
    receiveCallback = func;
}

/**
 * Polls the client for new input
 * Returns if the client times out
 */
void TCPClient::loop() {
    while(true){
        checkForNewMessage();
        //The client is dead break the loop
        if(isClientTimedOut()){
            close(sock_fd);
            return;
        }
    }
}

const char* TCPClient::checkForNewMessage() {
    //Check for the amount of bytes received
    char tempBuf[1024];
    int no_bytesReceived = recv(sock_fd,tempBuf,1024,MSG_PEEK);

    if(no_bytesReceived > 0){
        //Assign memory and call receive again to insert the bytes into the memory space.
        //Waits for the full message to be received
        const char* data = (char*)malloc(no_bytesReceived);
        recv(sock_fd, (void*)data, no_bytesReceived, 0);

        //Record the time of the message
        timeOfLastMessage = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        //Call back to the listener
        if(receiveCallback != nullptr){
            receiveCallback(data);
        }
        return data;
    }
    return nullptr;
}

bool TCPClient::isClientTimedOut() {
    double elapsedTime = difftime( time(nullptr), timeOfLastMessage);
    return elapsedTime > timeoutTimeInSeconds;
}

sockaddr_in TCPClient::getClientSockAddr() {
    return this->clientDetails;
}

size_t TCPClient::getClientSockAddrLen() {
    return this->addr_len;
}

void TCPClient::closeConnection() {
    close(sock_fd);
}




