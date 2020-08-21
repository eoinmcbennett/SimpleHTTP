//
// Created by Eoin on 12/07/2020.
//
#include <iostream>
#include <thread>
#include <vector>

void callback(uint16_t fd, char* data);
void newConn(TCPClient* client);
void disconCB(uint16_t fd);

std::vector<std::thread> clientThreads;

void serverThreadRunner();

void clientThreadRunner(TCPClient* client);



int main(){
    HTTPServer* server = new HTTPServer(5050);
    server->loop();
}