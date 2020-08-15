//
// Created by Eoin on 12/07/2020.
// Describes details of a connected client
//

#ifndef SERVERTEST_CLIENT_H
#define SERVERTEST_CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>

struct client {
    sockaddr_in clientDetails;
    int sock_fd;
};


#endif //SERVERTEST_CLIENT_H
