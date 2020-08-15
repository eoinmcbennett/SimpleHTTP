//
// Created by Eoin on 25/07/2020.
//

#ifndef SERVERTEST_WEBSOCKETSERVER_H
#define SERVERTEST_WEBSOCKETSERVER_H

#include "HTTPServer.h"

struct WebSocketClient {

};

class WebSocketServer : public HTTPServer  {
private:
    static Response* generate101(Request* request);

public:
    void loop();
    void onMessageReceived(uint16_t fd, char* message) override;
};


#endif //SERVERTEST_WEBSOCKETSERVER_H
