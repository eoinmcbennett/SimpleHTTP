//
// Created by Eoin on 15/08/2020.
//

#include "Connection.h"

void Connection::operator()(Socket conn_socket) {
    this->conn_socket = conn_socket;

    Request* request = receiveRequest();
}
