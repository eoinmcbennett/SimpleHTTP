//
// Created by Eoin on 06/08/2020.
//

#ifndef SERVERTEST_IOBSERVER_H
#define SERVERTEST_IOBSERVER_H

class HTTPClient;

class IObserver {
public:
    virtual void Update(HTTPClient* client,Request* request) =0;
};



#endif //SERVERTEST_IOBSERVER_H
