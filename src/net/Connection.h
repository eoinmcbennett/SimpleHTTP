//
// Created by Eoin on 15/08/2020.
//

#ifndef SERVERTEST_CONNECTION_H
#define SERVERTEST_CONNECTION_H

#include <chrono>

#include "Socket.h"
#include <arpa/inet.h>

/**
 * This class describes a client connection to the program
 */
class Connection {
protected:
    Socket conn_socket;
    time_t timeOfLastMessage;

public:
    explicit Connection(Socket socket);

    std::string getConnDetails();

};


#endif //SERVERTEST_CONNECTION_H
