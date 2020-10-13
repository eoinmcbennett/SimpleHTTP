//
// Created by Eoin on 22/08/2020.
//

#ifndef SERVERTEST_WEBSOCKETHANDLER_H
#define SERVERTEST_WEBSOCKETHANDLER_H

class WebsocketConnection;

class WebsocketHandler {
public:
    virtual void onConnect(WebsocketConnection connection) = 0;
    virtual void onDisconnect(WebsocketConnection connection) = 0;
    virtual void onData(WebsocketConnection connection, const char* data) = 0;
    virtual ~WebsocketHandler() = default;
};

#endif //SERVERTEST_WEBSOCKETHANDLER_H
