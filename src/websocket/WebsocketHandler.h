//
// Created by Eoin on 22/08/2020.
//

#ifndef SERVERTEST_WEBSOCKETHANDLER_H
#define SERVERTEST_WEBSOCKETHANDLER_H

class WebsocketConnection;

class WebsocketHandler {
public:
    virtual void onConnect(WebsocketConnection connection);
    virtual void onDisconnect(WebsocketConnection connection);
    virtual void onData(WebsocketConnection connection, const char* data);
};

#endif //SERVERTEST_WEBSOCKETHANDLER_H
