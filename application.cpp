//
// Created by Eoin on 12/07/2020.
//
#include <iostream>
#include <thread>
#include <vector>

class WebsocketHandler : public WSI{

    void onConnection(WebsocketConnection connection){

    }

    void onDisconnect(WebsocketConnection connection){

    }

    void onData(WebsocketConnection connection, const char* data){
        connection.send(data);
    }
};



int main(){
    HTTPServer(5050,"../Site");


}