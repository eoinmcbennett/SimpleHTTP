//
// Created by Eoin on 13/07/2020.
//

#ifndef SERVERTEST_HTTPSERVER_H
#define SERVERTEST_HTTPSERVER_H

#include "TCPServer.h"

#include <memory.h>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <string>
#include <chrono>
#include <ctime>

typedef enum METHOD{
    GET,
    POST,
    UNSUPPORTED
}METHOD;

typedef enum STATUS{
    OK,
    NOTFOUND,
    SWITCHINGPROTOCOLS
}STATUS;

typedef struct Header{
    char* fieldName;
    char* fieldData;
    struct Header* next;
}Header;

typedef struct Request{
    uint16_t sender;
    enum METHOD method;
    char* URL;
    char*version;
    struct Header* headers;
    char* body;

    bool fulfilled;
}Request;

typedef struct Response{
    char* version;
    char* statusCode;
    enum STATUS status;
    struct Header* headers;
    char* body;
}Response;



class HTTPServer : public TCPServer{
private:
    std::queue<Request*> requests;
    const char* sitePath;

    void(*requestReceivedCallback)(Request* request);
    void(*responseSentCallback)();

    struct Request* parseRequestFromRawData(const char* data);

    //test response
    const char* response1 = "HTTP/1.1 200 OK "
                           "Content-Type: text/html; charset=UTF-8"
                           "Content-Length: 53"
                           "\r\n"
                           "<!DOCTYPE html>"
                           "<html>"
                           "<h1>Well bai</h1>"
                           "</html>";

    //Override the tcp server receive function so we can get HTTP requests
    void onMessageReceived(uint16_t fd, char* message) override;

    void handleRequest(struct Request* request);

    Response* handleGetRequest(Request *pRequest);

    Response* handlePostRequest(Request *pRequest);

    Response* handleUnsupported(Request *pRequest);

    Response* generate404();


public:
    HTTPServer(const char* sitePath);
    HTTPServer();

public:
    void init();
    void loop() override;


    const char *formatResponse(Response *pResponse);

    void freeRequest(Request *request);
    void freeHeader(Header *header);
    void freeResponse(Response *response);
};




#endif //SERVERTEST_HTTPSERVER_H
