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
#include "src/http/HTTPServer.h"

/*
 *





 */


void* operator new(size_t size){
    void* mem = malloc(size);
    std::cout << "Allocated " << size << " bytes at " << mem << std::endl;
    return mem;
}

void operator delete(void* memory){
    std::cout << "Freed memory at " << memory << std::endl;
    free(memory);
}

class RaspiStreamWebsocketHandler : public WebsocketHandler{

    void onConnect(WebsocketConnection connection) override {

    }

    void onDisconnect(WebsocketConnection connection ) override {

    }

    void onData(WebsocketConnection connection, const char* data) override {

    }
};


int main(){
    HTTPServer server(8080,"","../../site",2);

    while(true){
        server.listenForIncoming();
    }
}
