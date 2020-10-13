//
// Created by Eoin on 09/10/2020.
//

#include <cstring>

#include "Response.h"

/**
 * Handles conversion of a response to a raw string
 * @param response
 * @return pointer to the string response
 */
const char* Response::convertResponseToString(Response* response) {

    std::string formattedRes;
    formattedRes += response->version;
    formattedRes += ' ';
    formattedRes += response->statusCode;
    formattedRes += ' ';

    //Convert the status to its string representation
    switch(response->status){
        case OK : formattedRes += "OK";
        case NOTFOUND : formattedRes += "Not Found";
        case SWITCHINGPROTOCOLS : formattedRes += "Switching Protocols";
        case BADREQUEST : formattedRes += "Bad Request";
        case INTERNALSERVERERROR : formattedRes += "Internal Server Error";
    }

    formattedRes += "\r\n";

    //Turn header content into strings
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

    char* data = new char[formattedRes.length()];
    strcpy(data,formattedRes.c_str());

    return data;
}