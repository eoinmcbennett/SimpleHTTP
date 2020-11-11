//
// Created by Eoin on 30/07/2020.
//

#ifndef SERVERTEST_REQUEST_H
#define SERVERTEST_REQUEST_H


#include "Method.h"
#include "Header.h"

class HTTPConnection;

struct Request {
public:
    const char* version;
    enum METHOD method;
    const char* URL;
    struct Header* headers;
    char* body;
    HTTPConnection* sender;

    static Request* getRequestFromRawString(const char* data);
};

#endif //SERVERTEST_REQUEST_H
