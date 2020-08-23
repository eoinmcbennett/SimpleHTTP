//
// Created by Eoin on 30/07/2020.
//

#ifndef SERVERTEST_REQUEST_H
#define SERVERTEST_REQUEST_H

#include <strings.h>
#include <cstring>
#include "HTTPObject.h"
#include "Method.h"
#include "Header.h"


struct Request : public HTTPObject{
public:
    std::string version;
    enum METHOD method;
    std::string URL;
    struct Header* headers;
    std::string body;

    static Request* getRequestFromRawString(const char* data){
        Request* res = new Request;
        bzero(res,sizeof(struct Request));

        unsigned char method_Len = strcspn(data," ");
        if(memcmp(data,"GET",strlen("GET")) == 0)
            res->method = GET;
        else
            res->method = UNSUPPORTED;
        //Move the pointer past the space
        data += method_Len + 1;

        //Handle the url storage
        unsigned int url_Len = strcspn(data," ");
        res->URL = std::string(data,data+url_Len);
        data+= url_Len + 1; //Push the pointer to the version

        //Handle version storage
        unsigned char version_Len = strcspn(data,"\r\n");
        res->version = std::string(data,data+version_Len);
        data += version_Len + 2; //Push data pointer into currentHeader field


        struct Header* currentHeader = nullptr;
        struct Header* last = nullptr;

        while(data[0] != '\r' || data[1] != '\n'){
            last = currentHeader;
            currentHeader = new Header;

            //Handle the currentHeader name
            unsigned int name_len = strcspn(data,":");
            currentHeader->fieldName = std::string(data, data+name_len);
            data += name_len + 1; //Move past the :

            //Move past any white space
            while(*data == ' '){
                data++;
            }

            //Handle header field data storage
            unsigned int data_len = strcspn(data,"\r\n");
            currentHeader->fieldData = std::string(data,data+data_len);
            data += data_len + 2; //Move past CRLF

            currentHeader->next = last;
        }
        res->headers = last;
        data += 2;

        unsigned int body_len = strcspn(data,"\0");
        res->body = std::string(data,data+body_len);

        return res;
    }
};

#endif //SERVERTEST_REQUEST_H
