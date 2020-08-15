//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_HEADER_H
#define SERVERTEST_HEADER_H

#include <string>

struct Header{
    std::string fieldName;
    std::string fieldData;
    Header* next;
};
#endif //SERVERTEST_HEADER_H
