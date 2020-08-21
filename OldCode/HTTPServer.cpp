//
// Created by Eoin on 13/07/2020.
//



#include <sstream>
#include "HTTPServer.h"

HTTPServer::HTTPServer() {}

struct Request *HTTPServer::parseRequestFromRawData(const char *data) {
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
        res->method = GET;
    else
        res->method = UNSUPPORTED;

    //Move the pointer past the space
    data += method_Len + 1;

    //Handle the url storage
    unsigned int url_Len = strcspn(data," ");

    res->URL = allocateString(url_Len);

    //If space for the url could not be allocated free the whole request and return back;
    if(!res->URL){
        return nullptr;
    }

    //Copy the url from the raw request and add the null terminator
    memcpy(res->URL,data,url_Len);


    data+= url_Len + 1;

    //Handle version storage
    unsigned char version_Len = strcspn(data,"\r\n");

    res->version = allocateString(version_Len);

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

        currentHeader->fieldName = allocateString(name_len);

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
        currentHeader->fieldData = allocateString(data_len);

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

    res->body = allocateString(body_len);

    if(!res->body){
        return nullptr;
    }

    memcpy(res->body,data,body_len);


    return res;
}

void HTTPServer::loop() {
    TCPServer::loop();


    //Handle http requests if they exist
    if(!requests.empty()){

    }
}

void HTTPServer::init() {
}

void HTTPServer::onMessageReceived(uint16_t fd, char *message)  {
    struct Request* request;
    request = parseRequestFromRawData(message);

    std::cout << "Method: " << request->method << std::endl;
    std::cout << "URL: " << request->URL << std::endl;
    std::cout << "Version: " << request->version << std::endl;

    struct Header* currentHeader = request->headers;

    std::cout << "Headers: " << std::endl;
    while(currentHeader != nullptr){
        std::cout << "Name: " << currentHeader->fieldName << " " << "Value: " << currentHeader->fieldData << std::endl;
        currentHeader = currentHeader->next;
    }

    std::cout << "Body: " << std::endl;
    std::cout << request->body << std::endl;

    request->sender = fd;
    //Push the request onto the queue
    handleRequest(request);

}

HTTPServer::HTTPServer(const char *sitePath) {

}

void HTTPServer::handleRequest(struct Request *request) {
    //Fill out the response we will send
    Response* response;

    //Handle the response
    switch(request->method){
        case 0: response = handleGetRequest(request); break;
        case 1: response = handlePostRequest(request); break;
        case 2: response = handleUnsupported(request); break;
    }

    //Free the request were done with it

    //Send the response
    const char* formattedResponse = formatResponse(response);



    sendMessage(request->sender, formattedResponse);
    freeRequest(request);
    freeResponse(response);

}


void HTTPServer::freeRequest(Request* request){
    //Free request headers
    Header* temp = request->headers;
    while(request->headers){
        temp = request->headers;
        request->headers = request->headers->next;
        freeHeader(temp);
    }
    free(request->body);
    free(request->URL);
    free(request->version);
    free(request);
}

void HTTPServer::freeHeader(Header* header){
    if(header){
        if(header->fieldName)
            free(header->fieldName);
        if(header->fieldData)
            free(header->fieldData);
        free(header);
    }
    return;
}

void HTTPServer::freeResponse(Response *response) {
    Header* temp = response->headers;
    while(response->headers){
        temp = response->headers;
        response->headers = response->headers->next;
        freeHeader(temp);
    }

    free(response->version);
    free(response->body);
}

Response* HTTPServer::handleGetRequest(Request *pRequest) {
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


    Header* header = (Header*)malloc(sizeof(Header));
    Header* header1 = (Header*)malloc(sizeof(Header));

    header->fieldName = allocateString(sizeof("Content-Type"));
    strcpy(header->fieldName,"Content-Type");

    header->fieldData = allocateString(sizeof("text/html"));
    strcpy(header->fieldData,"text/html");

    header1->fieldName = allocateString(sizeof("charset"));
    strcpy(header1->fieldName,"charset");

    header1->fieldData = allocateString(sizeof("UTF-8"));
    strcpy(header1->fieldData,"UTF-8");

    header->next = header1;







    Header* header2 = (Header*)malloc(sizeof(Header));
    header2->fieldName = allocateString(sizeof("Content-Length"));
    strcpy(header2->fieldName,"Content-Length");

    header1->next = header2;

    unsigned int fileLength = 0;

    //Get the whole length of the file
    while(fgetc(file) != EOF){
        fileLength++;
    }

    header2->fieldData = allocateString(10);
    sprintf(header2->fieldData,"%d",fileLength);

    header2->next = nullptr;


    //Rewind the pointer
    rewind(file);

    //pre allocate space for the file
    response->body = allocateString(fileLength);

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

Response* HTTPServer::handlePostRequest(Request *pRequest) {
    Response* response;
}

Response* HTTPServer::handleUnsupported(Request *pRequest) {
    Response* response;
}

const char *HTTPServer::formatResponse(Response *pResponse) {
    char *stringResponse = allocateString(10000);
    strcpy(stringResponse,"http/1.1 ");


    strcat(stringResponse,pResponse->statusCode);

    switch(pResponse->status){
        case OK: strcat(stringResponse," OK\r\n"); break;
        case NOTFOUND: strcat(stringResponse, " Not Found\r\n"); break;
    }


    struct Header* header = pResponse->headers;

    while(header != nullptr){
        strcat(stringResponse,header->fieldName);
        strcat(stringResponse,": ");
        strcat(stringResponse,header->fieldData);
        strcat(stringResponse,"\r\n");
        header = header->next;
    }
    strcat(stringResponse,"\r\n");

    if(pResponse->body){
        strcat(stringResponse,pResponse->body);
    }

 return stringResponse;
}

Response *HTTPServer::generate404() {
    //Allocate the response
    Response* response = (Response*)malloc(sizeof(Response));
    bzero(response,sizeof(Response));

    //Allocate and assign the status line
    response->version = allocateString(sizeof("http/1.1 "));
    strcpy(response->version,"http/1.1");

    response->statusCode = allocateString(sizeof("404"));
    strcpy(response->statusCode,"404");

    response->status = NOTFOUND;

    //Allocate response headers
    Header* date = (Header*)malloc(sizeof(Header));

    date->fieldName = allocateString(sizeof("Date"));
    strcpy(date->fieldName,"Date");

    //Grab the current time for the request
    std::time_t timeOfRequest = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char* data = std::ctime(&timeOfRequest);
    date->fieldData = allocateString(strlen(data) - 1);
    data[strlen(data) - 1] = '\0';
    strcpy(date->fieldData,data);



    Header* server = (Header*)malloc(sizeof(Header));
    server->fieldName = allocateString(sizeof("Server"));
    strcpy(server->fieldName,"Server");

    server->fieldData = allocateString(sizeof("Simple http"));
    strcpy(server->fieldData,"Simple http");



    Header* header2 = (Header*)malloc(sizeof(Header));

    header2->fieldName = allocateString(sizeof("Content-Length"));
    strcpy(header2->fieldName,"Content-Length");

    header2->fieldData = allocateString(sizeof('0'));
    strcpy(header2->fieldData,"0");

    header2->next = nullptr;
    date->next = header2;
    server->next = date;

    response->headers = server;

    return response;
}
