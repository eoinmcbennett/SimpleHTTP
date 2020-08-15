//
// Created by Eoin on 30/07/2020.
//

#ifndef SERVERTEST_REQUEST_H
#define SERVERTEST_REQUEST_H

#include "Method.h"
#include "Header.h"


struct Request{

    char* version;
    enum METHOD method;
    char* URL;
    struct Header* headers;
    char* body;
};

#endif //SERVERTEST_REQUEST_H
