//
// Created by Eoin on 29/07/2020.
//

#ifndef SERVERTEST_RESPONSE_H
#define SERVERTEST_RESPONSE_H

#include "Header.h"
#include "Status.h"

struct Response  {
    char* version;
    char* statusCode;
    enum STATUS status;
    struct Header* headers;
    char* body;

    static const char* convertResponseToString(Response* response);
};

#endif //SERVERTEST_RESPONSE_H
