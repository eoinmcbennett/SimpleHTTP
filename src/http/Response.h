//
// Created by Eoin on 29/07/2020.
//

#ifndef SERVERTEST_RESPONSE_H
#define SERVERTEST_RESPONSE_H

#include "Header.h"
#include "Status.h"

class HTTPConnection;

struct Response  {
    const char* version;
    const char* statusCode;
    enum STATUS status;
    struct Header* headers;
    char* body;
    HTTPConnection* recipient;

    static const char* convertResponseToString(Response* response);
};

#endif //SERVERTEST_RESPONSE_H
