//
// Created by Eoin on 29/07/2020.
//

#include "HTTPClient.h"


//Class constructors
HTTPClient::HTTPClient(unsigned short sock_fd, HTTPServer &server) :
TCPClient(sock_fd), server(server) {

}


/**
 * Checks for input from the client and if they have timed out
 */
void HTTPClient::loop() {
    while(true){
        Request* request = checkForNewRequest();
        if(request && newRequestCallback){
            server.handleRequest(this,request);
        }
        if(TCPClient::isClientTimedOut()){
            TCPClient::closeConnection();
            freeClient();
            return;
        }
    }
}

/**
 * Checks for a new request from the client and returns this value
 * @return
 */
Request* HTTPClient::checkForNewRequest() {
    const char* message = TCPClient::checkForNewMessage();
    Request* request = parseRequestFromRawData(message);
    return request;
}

/**
 * Sends the given response back to the client
 * @param response - The response to be sent
 * @return - status int
 */
int HTTPClient::send(Response *response) {
    const char* data = convertResponseToRawData(response);
    unsigned int res_length = strlen(data);
    TCPClient::sendToClient(data,res_length);
}

/**
 * Converts a response struct back to its HTTP string form for sending
 * @param response - The response to be converted
 * @return A pointer to the beginning of the string
 */
const char* convertResponseToRawData(Response* response){
    char *stringResponse = Util::allocateString(10000);
    strcpy(stringResponse,"HTTP/1.1 ");

    strcat(stringResponse,response->statusCode);

    switch(response->status){
        case OK: strcat(stringResponse," OK\r\n"); break;
        case NOTFOUND: strcat(stringResponse, " Not Found\r\n"); break;
    }


    struct Header* header = response->headers;

    while(header != nullptr){
        strcat(stringResponse,header->fieldName);
        strcat(stringResponse,": ");
        strcat(stringResponse,header->fieldData);
        strcat(stringResponse,"\r\n");
        header = header->next;
    }
    strcat(stringResponse,"\r\n");

    if(response->body){
        strcat(stringResponse,response->body);
    }
    return stringResponse;
}

/**
 * Parses a request from raw data sent to the socket
 * @param data
 * @return
 */
Request *HTTPClient::parseRequestFromRawData(const char *data) {
    //Assign memory to store the request
    Request *res = (Request*)malloc(sizeof(struct Request));

    //Check for valid memory assignment
    if(!res){
        return nullptr;
    }

    //Zero out the new memory block
    bzero(res,sizeof(struct Request));

    //Store the request data
    unsigned char method_Len = strcspn(data," ");

    if(memcmp(data,"GET",strlen("GET")) == 0)
        res->method = GET;
    else if(memcmp(data,"POST",strlen("POST")) == 0)
        res->method = POST;
    else
        res->method = UNSUPPORTED;

    //Move the pointer past the space
    data += method_Len + 1;

    //Handle the url storage
    unsigned int url_Len = strcspn(data," ");

    res->URL = Util::allocateString(url_Len);

    //If space for the url could not be allocated free the whole request and return back;
    if(!res->URL){
        return nullptr;
    }

    //Copy the url from the raw request and add the null terminator
    memcpy(res->URL,data,url_Len);


    data+= url_Len + 1;

    //Handle version storage
    unsigned char version_Len = strcspn(data,"\r\n");

    res->version = Util::allocateString(version_Len);

    if(!res->version){
        return nullptr;
    }

    memcpy(res->version,data,version_Len);

    data += version_Len + 2; //Push data pointer into currentHeader field


    struct Header* currentHeader = nullptr;
    struct Header* last = nullptr;

    while(data[0] != '\r' || data[1] != '\n'){

        last = currentHeader;

        //Handle the currentHeader name
        currentHeader = (Header*)malloc(sizeof(struct Header));

        unsigned int name_len = strcspn(data,":");
        currentHeader->fieldName = Util::allocateString(name_len);
        if(!currentHeader->fieldName){
            //Free the data
            return nullptr;
        }

        memcpy(currentHeader->fieldName,data,name_len);
        currentHeader->fieldName[name_len] = '\0';

        data += name_len + 1; //Move past the :

        //Move past any white space
        while(*data == ' '){
            data++;
        }

        unsigned int data_len = strcspn(data,"\r\n");
        currentHeader->fieldData = Util::allocateString(data_len);

        if(!currentHeader->fieldData){
            return nullptr;
        }

        memcpy(currentHeader->fieldData,data,data_len);
        currentHeader->fieldData[data_len] = '\0';

        data += data_len + 2; //Move past CRLF

        currentHeader->next = last;

    }

    res->headers = last;
    data += 2;

    unsigned int body_len = 0;

    res->body = Util::allocateString(body_len);

    if(!res->body){
        return nullptr;
    }
    memcpy(res->body,data,body_len);
    return res;
}

void HTTPClient::setNewRequestCallback(void (*callback)(HTTPClient *, Request *)) {
    this->newRequestCallback = callback;
}

void HTTPClient::setClientServerInstance(HTTPServer &server) {
    this->server = server;
}

void freeClient(){

}

