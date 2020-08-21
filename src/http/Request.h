//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_REQUEST_H
#define SERVERTEST_REQUEST_H

#include <string>

#include "Header.h"

class Request {
private:
    std::string statusLine;
    Header* headers;
    std::string body;
};


#endif //SERVERTEST_REQUEST_H
