//
// Created by Eoin on 29/07/2020.
//

#ifndef SERVERTEST_HTTPCLIENT_H
#define SERVERTEST_HTTPCLIENT_H

#include "../TCP/TCPClient.h"
#include "../Util.h"
#include "../WebSocket/WebSocketClient.h"

#include "Response.h"
#include "Method.h"
#include "Request.h"
/**
 * Represents a HTTP Client who is connected to the server
 */
class HTTPClient : public TCPClient {
private:
    WebSocketClient websocketClient;



public:
    explicit HTTPClient(unsigned short sock_fd);

    int send(Response* response);

    void loop() override;

    void setNewRequestCallback(void(*callback)(HTTPClient*,Request*));



private:
    Request* checkForNewRequest();
    Request* parseRequestFromRawData(const char* data);

    const char* convertResponseToRawData(Response* response);

    void freeClient();

protected:
    void(*newRequestCallback)(HTTPClient*,Request*);

};


#endif //SERVERTEST_HTTPCLIENT_H
