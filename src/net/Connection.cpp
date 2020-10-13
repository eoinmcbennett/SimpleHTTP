//
// Created by Eoin on 15/08/2020.
//

#include "Connection.h"

/**
 * Initialises and instance of connection
 * @param socket
 */
Connection::Connection(Socket* socket) {
    this->conn_socket = socket;
    this->timeOfLastMessage = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

std::string Connection::getConnDetails() {
    std::string details;

    details.append("IP: ");
    details.append(inet_ntoa(this->conn_socket->getSocketAddr().sin_addr));
    details.append("\nPort: " + std::to_string(ntohs(this->conn_socket->getSocketAddr().sin_port)));
    details.append("\nTime of last message: ");
    details.append(ctime(&this->timeOfLastMessage));

    return details;
}


