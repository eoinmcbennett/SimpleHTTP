//
// Created by Eoin on 27/10/2020.
// These methods handle generation of basic HTTP responses.
// Should be used to communicate issues with the client
//

#include <ctime>
#include "Responses.h"
#include "Response.h"

static const char* getCurTime(){
    std::time_t now = std::time(nullptr);
    return ctime(&now);
}

static void generate400Response(Response*& response){
    if(response == nullptr){
        return;
    }
    response->version = "HTTP/1.1";
    response->statusCode = "400";
    response->status = BADREQUEST;
    response->headers = new Header("Date",getCurTime());
    response->headers->next = new Header("Server","SimpleHTTP");
    response->body = nullptr;
}

static void generate401Response(Response*& response){
    if(response == nullptr){
        return;
    }
    response->version = "HTTP/1.1";
    response->statusCode = "401";
    response->status = UNAUTHORISED;
    response->body = nullptr;
    response->headers = new Header("Server","SimpleHTTP");
    response->headers->next = new Header("Date",getCurTime());

}

static void generate403Response(Response*& response){
    if(response == nullptr){
        return;
    }
    response->version = "HTTP/1.1";
    response->statusCode = "403";
    response->status = FORBIDDEN;
    response->body = nullptr;
    response->headers = new Header("Server","SimpleHTTP");
    response->headers->next = new Header("Date",getCurTime());
}

static void generate404Response(Response*& response){
    if(response == nullptr){
        return;
    }
    response->version = "HTTP/1.1";
    response->statusCode = "404";
    response->status = NOTFOUND;
    response->body = nullptr;
    response->headers = new Header("Server","SimpleHTTP");
    response->headers->next = new Header("Date",getCurTime());
}

static void generate500Response(Response*& response){
    if(response == nullptr){
        return;
    }
    response->version = "HTTP/1.1";
    response->statusCode = "500";
    response->status = INTERNALSERVERERROR;
    response->body = nullptr;
    response->headers = new Header("Server","SimpleHTTP");
    response->headers->next = new Header("Date",getCurTime());
}

static void generate501Response(Response*& response){
    if(response == nullptr){
        return;
    }
    response->version = "HTTP/1.1";
    response->statusCode = "501";
    response->status = NOTIMPLEMENTED;
    response->body = nullptr;
    response->headers = new Header("Server","SimpleHTTP");
    response->headers->next = new Header("Date",getCurTime());
}