//
// Created by Eoin on 14/07/2020.
//

#ifndef SERVERTEST_HTTPREQUEST_H
#define SERVERTEST_HTTPREQUEST_H

#include <map>
#include <vector>

#define SP ' '
#define LF '\n'
#define CR '\r'
#define COLON ':'
#define VERSION = "HTTP/1.1"

class HTTPRequest {
private:
    //Status line
    char* method;
    char* url;
    char* version;

    //Header
    std::map<char*,char*> headerFields;

    char* requestBody;

public:
    HTTPRequest();
    //Takes in a raw request and splits it into fields usable by this class
    HTTPRequest(char* data);

    char* getMethod();
    char* getURL();
    char* getVersion();

    std::map<char*,char*> getHeaderFields();

    char* getRequestBody();


private:
    void parseHTTPData(char* data);



};


#endif //SERVERTEST_HTTPREQUEST_H
