//
// Created by Eoin on 12/07/2020.
//
#include <iostream>
#include <thread>
#include <vector>
#include <future>


#include "src/http/HTTPServerSocket.h"
#include "src/websocket/WebsocketHandler.h"
#include "src/websocket/WebsocketConnection.h"

class RaspiStreamWebsocketHandler : public WebsocketHandler{

    void onConnect(WebsocketConnection connection) override {

    }

    void onDisconnect(WebsocketConnection connection ) override {

    }

    void onData(WebsocketConnection connection, const char* data) override {

    }
};


int main(){
    HTTPServerSocket* socket = new HTTPServerSocket(5050);

    while(true){
        HTTPConnection* connection = socket->AcceptConnection();

        std::cout << "Client connected to server socket" << std::endl;

        std::cout << connection->getConnDetails() << std::endl;
    }
}
