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
};

#endif //SERVERTEST_RESPONSE_H
