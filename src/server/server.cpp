//
// Created by kowal on 21.04.18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include "server.h"
#include "connection.h"
#include "connection_exception.h"

namespace server {
    server::server(unsigned int port) : port{port}, server_address{}, log{} {
        this->sock = socket(PF_INET, SOCK_STREAM, 0);
        if (this->sock < 0) {
            throw connection_exception("Failed to create socket");
        }

        this->server_address.sin_family = AF_INET;
        this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        this->server_address.sin_port = htons(static_cast<uint16_t>(port));

        if (bind(sock, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) < 0) {
            throw connection_exception("Failed to bind socket to address");
        }

        if (listen(sock, QUEUE_SIZE) < 0) {
            throw connection_exception("Failed to switch to listening mode");
        }
    }

    connection server::next_connection() {
        struct sockaddr client_address{};
        socklen_t client_address_len = sizeof(client_address);
        int msg_sock = accept(this->sock, &client_address, &client_address_len);
        if (msg_sock < 0) {
            throw connection_exception("Failed to accept a connection on server socket");
        }
        return connection(msg_sock, this->log);
    }

    server::~server() {
        if(close(this->sock) < 0) {
            log.error("Failed to close server socket ", this->sock);
        }
    }
}
