//
// Created by Eoin on 12/07/2020.
//
#include <iostream>
#include <thread>
#include "TCP/TCPServer.h"
#include <vector>

void callback(uint16_t fd, char* data);
void newConn(TCPClient* client);
void disconCB(uint16_t fd);

std::vector<std::thread> clientThreads;

void serverThreadRunner();

void clientThreadRunner(TCPClient* client);

TCPServer server(5050);

std::thread serverThread;

int main() {
    serverThread = std::thread(serverThreadRunner);

    std::cin.get();
}

void serverThreadRunner(){
    server.setNewConnectionCallback(newConn);
    while(true){
        server.loop();
    }
}

void newConn(TCPClient* client){
    clientThreads.emplace_back(clientThreadRunner,client);
}

void clientThreadRunner(TCPClient* client){
    while(true){
        client->loop();
    }
}

void disconCB(uint16_t fd){
    std::cout << fd << " disconnected" << std::endl;
}
