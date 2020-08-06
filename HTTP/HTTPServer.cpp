//
// Created by Eoin on 30/07/2020.
//

#include "HTTPServer.h"

HTTPServer::HTTPServer(unsigned short port, unsigned int maxClients, unsigned int clientTimeoutTime, const char *sitePath) :
TCPServer(port,maxClients,clientTimeoutTime) {
    if(sitePath != nullptr){
        this->sitePath = sitePath;
    }
}

/**
 * Checks for new HTTP Clients attempting to connect to the server
 * @return
 */
HTTPClient* HTTPServer::checkForNewClients() {
    HTTPClient* client = (HTTPClient*)TCPServer::checkForNewClients();

    clientThreads.emplace_back(clientThreadRunner,client);
}

/**
 * Controls how HTTP requests are handled within the server
 * Generates a response and calls send for the client
 * @param sender - The client sending the request
 * @param request - The request being sent
 */
void HTTPServer::handleRequest(HTTPClient *sender, Request *request) {
    Response* response;
    //Handle the request depending on what method it is
    switch(request->method){
        case GET: response = handleGetRequest(request); break;
        case POST: response = handlePostRequest(request); break;
        case UNSUPPORTED: response = handleUnsupportedRequest(request); break;
    }
    //Send the response to the client
    sender->send(response);
}

/**
 * Handles updating for the server
 */
void HTTPServer::loop() {
    while(true){
        checkForNewClients();
    }
}


/**
 * Static method to allow for thread starting
 * Ensures each client is on a new thread allowing simultanious request processing
 * @param client - the new client
 */
void HTTPServer::clientThreadRunner(HTTPClient *client) {
    if(client == nullptr){
        return;
    }
    client->loop();
}

/**
 * Handles a HTTP Get request
 * @param pRequest - The request to handle
 * @return A response to the request
 */
Response *HTTPServer::handleGetRequest(Request *pRequest) {
    Response* response = (Response*)malloc(sizeof(Response));
    bzero(response,sizeof(Response));

    FILE* file;
    char* filePath;

    if(sitePath == nullptr){
        filePath = pRequest->URL;
    }else{
        filePath = strcat((char*)sitePath,pRequest->URL);
    }

    if(memcmp(pRequest->URL,"/",sizeof("/")) == 0){
        file = fopen("../index.html","r");
    }else{
        file = fopen(filePath,"r");
    }

    //404 not found
    if(file == nullptr) {
        response->status = NOTFOUND;
        response->statusCode = "404";

        freeResponse(response);
        return generate404();
    }

    //200 OK
    response->status = OK;
    response->statusCode = "200";

    //Assign headers
    Header* header = (Header*)malloc(sizeof(Header));
    Header* header1 = (Header*)malloc(sizeof(Header));

    header->fieldName = Util::allocateString(sizeof("Content-Type"));
    strcpy(header->fieldName,"Content-Type");

    header->fieldData = Util::allocateString(sizeof("text/html"));
    strcpy(header->fieldData,"text/html");

    header1->fieldName = Util::allocateString(sizeof("charset"));
    strcpy(header1->fieldName,"charset");

    header1->fieldData = Util::allocateString(sizeof("UTF-8"));
    strcpy(header1->fieldData,"UTF-8");

    header->next = header1;


    Header* header2 = (Header*)malloc(sizeof(Header));
    header2->fieldName = Util::allocateString(sizeof("Content-Length"));
    strcpy(header2->fieldName,"Content-Length");

    header1->next = header2;

    //Get the file length of the response for the content length header
    unsigned int fileLength = 0;

    //Get the whole length of the file
    while(fgetc(file) != EOF){
        fileLength++;
    }

    header2->fieldData = Util::allocateString(10);
    sprintf(header2->fieldData,"%d",fileLength);
    header2->next = nullptr;
    //Rewind the pointer
    rewind(file);

    //pre allocate space for the file
    response->body = Util::Util::allocateString(fileLength);

    //Write the file contents into the memory buffer
    int curChar = fgetc(file);
    for(int i = 0; i < fileLength; i++){
        response->body[i] = curChar;
        curChar = fgetc(file);
    }

    //Close the file
    fclose(file);

    response->headers = header;

    return response;
}

/**
 * Handles a HTTP Post request
 * @param pRequest The request to handle
 * @return A response to the request
 */
Response *HTTPServer::handlePostRequest(Request *pRequest) {
    return nullptr;
}

/**
 * Handles a Unsupported HTTP method
 * @param pRequest The request to handle
 * @return A response to the request
 */
Response *HTTPServer::handleUnsupportedRequest(Request *pRequest) {
    return nullptr;
}


/**
 * Generates a 404 response for a request
 * @return
 */
Response *HTTPServer::generate404() {
    //Allocate the response
    Response* response = (Response*)malloc(sizeof(Response));
    bzero(response,sizeof(Response));

    //Allocate and assign the status line
    response->version = Util::allocateString(sizeof("HTTP/1.1 "));
    strcpy(response->version,"HTTP/1.1");

    response->statusCode = Util::allocateString(sizeof("404"));
    strcpy(response->statusCode,"404");

    response->status = NOTFOUND;

    //Allocate response headers
    Header* date = (Header*)malloc(sizeof(Header));

    date->fieldName = Util::allocateString(sizeof("Date"));
    strcpy(date->fieldName,"Date");

    //Grab the current time for the request
    std::time_t timeOfRequest = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char* data = std::ctime(&timeOfRequest);
    date->fieldData = Util::allocateString(strlen(data) - 1);
    data[strlen(data) - 1] = '\0';
    strcpy(date->fieldData,data);



    Header* server = (Header*)malloc(sizeof(Header));
    server->fieldName = Util::allocateString(sizeof("Server"));
    strcpy(server->fieldName,"Server");

    server->fieldData = Util::allocateString(sizeof("Simple HTTP"));
    strcpy(server->fieldData,"Simple HTTP");



    Header* header2 = (Header*)malloc(sizeof(Header));

    header2->fieldName = Util::allocateString(sizeof("Content-Length"));
    strcpy(header2->fieldName,"Content-Length");

    header2->fieldData = Util::allocateString(sizeof('0'));
    strcpy(header2->fieldData,"0");

    header2->next = nullptr;
    date->next = header2;
    server->next = date;

    response->headers = server;

    return response;
}
