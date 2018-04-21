//
// Created by kowal on 21.04.18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include "connection.h"

namespace server {
    connection::connection(unsigned int port) : port{port}, server_address{} {
        this->sock = socket(PF_INET, SOCK_STREAM, 0);
        if(this->sock < 0) {
            throw connection_exception("Failed to create socket");
        }

        this->server_address.sin_family = AF_INET;
        this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        this->server_address.sin_port = htons(static_cast<uint16_t>(port));

        if(bind(sock, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) < 0) {
            throw connection_exception("Failed to bind socket to address");
        }

        if(listen(sock, server::QUEUE_SIZE) < 0) {
            throw connection_exception("Failed to switch to listening mode");
        }
    }

    const char * connection_exception::what() const noexcept {
        return strcat(const_cast<char *>("CONNECTION ERROR: "), message.c_str());
    }
}
