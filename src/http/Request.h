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
    char* version;
    enum METHOD method;
    char* URL;
    struct Header* headers;
    char* body;

    static Request* getRequestFromRawString(const char* data);
};

#endif //SERVERTEST_REQUEST_H
