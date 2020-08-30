//
// Created by Eoin on 29/07/2020.
//

#ifndef SERVERTEST_RESPONSE_H
#define SERVERTEST_RESPONSE_H

#include "Header.h"
#include "Status.h"
#include "HTTPObject.h"

struct Response : public HTTPObject {
    std::string version;
    std::string statusCode;
    enum STATUS status;
    struct Header* headers;
    std::string body;

    static std::string convertResponseToString(Response* response);
};

/**
 * Handles conversion of a response to a raw string
 * @param response
 * @return
 */
std::string Response::convertResponseToString(Response *response) {
    std::string formattedRes;
    formattedRes += response->version + ' ';
    formattedRes += response->statusCode + ' ';

    //Convert the status to its string representation
    switch(response->status){
        case OK : formattedRes += "OK";
        case NOTFOUND : formattedRes += "Not Found";
        case SWITCHINGPROTOCOLS : formattedRes += "Switching Protocols";
        case BADREQUEST : formattedRes += "Bad Request";
        case INTERNALSERVERERROR : formattedRes += "Internal Server Error";
    }

    formattedRes += "\r\n";

    Header* curHeader = response->headers;
    while(curHeader != nullptr){
        formattedRes += curHeader->fieldName;
        formattedRes += ": ";
        formattedRes += curHeader->fieldData;
        formattedRes += "\r\n";

        curHeader = response->headers->next;
    }
    formattedRes += "\r\n";
    formattedRes += response->body;
    formattedRes += "\r\n";

    return formattedRes;
}

#endif //SERVERTEST_RESPONSE_H
