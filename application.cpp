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
#include "src/http/Response.h"

class RaspiStreamWebsocketHandler : public WebsocketHandler{

    void onConnect(WebsocketConnection connection) override {

    }

    void onDisconnect(WebsocketConnection connection ) override {

    }

    void onData(WebsocketConnection connection, const char* data) override {

    }
};


int main(){

    Response response;
    response.version = "HTTP/1.1";
    std::cout << sizeof(response) << std::endl;
    response.statusCode = "200";
    std::cout << sizeof(response) << std::endl;

    while(true){

    }
}
