//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_HEADER_H
#define SERVERTEST_HEADER_H

#include <string>
#include <utility>

struct Header{
    std::string fieldName;
    std::string fieldData;
    Header* next;

    Header(std::string fieldName, std::string fieldData){
        this->fieldName = std::move(fieldName);
        this->fieldData = std::move(fieldData);
        this->next = nullptr;
    }

    Header(){
        this->next = nullptr;
    }
};
#endif //SERVERTEST_HEADER_H
