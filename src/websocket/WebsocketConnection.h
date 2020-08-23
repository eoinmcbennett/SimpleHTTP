//
// Created by Eoin on 22/08/2020.
//

#ifndef SERVERTEST_WEBSOCKETCONNECTION_H
#define SERVERTEST_WEBSOCKETCONNECTION_H

#include "../net/Connection.h"

class WebsocketConnection : public Connection{
public:
    WebsocketConnection(Socket socket);

    void init();
    void send();
};


#endif //SERVERTEST_WEBSOCKETCONNECTION_H
