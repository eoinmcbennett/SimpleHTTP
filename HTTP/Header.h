//
// Created by Eoin on 30/07/2020.
//

#ifndef SERVERTEST_HEADER_H
#define SERVERTEST_HEADER_H

/**
 * Defines a HTTP Request/Response header field
 */
struct Header {
    char* fieldName;
    char* fieldData;
    Header* next;
};

#endif //SERVERTEST_HEADER_H
