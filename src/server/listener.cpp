//
// Created by kowal on 21.04.18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include "listener.h"
#include "connection.h"
#include "connection_exception.h"

namespace server {
    listener::listener() : port{}, sock{-1}, server_address{}, log{"EMPTY SERVER"} {}

    listener::listener(unsigned int port) : port{port}, server_address{}, log{"SERVER"} {
        log.status("Starting...");

        this->sock = socket(PF_INET, SOCK_STREAM, 0);
        if (this->sock < 0) {
            log.error(std::strerror(errno));
            throw connection_exception("Failed to create socket");
        }

        this->server_address.sin_family = AF_INET;
        this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        this->server_address.sin_port = htons(static_cast<uint16_t>(port));
        if (bind(this->sock, (sockaddr *)(&(this->server_address)), sizeof(this->server_address)) < 0) {
            log.error(std::strerror(errno));
            throw connection_exception("Failed to bind socket to address");
        }

        if (listen(this->sock, QUEUE_SIZE) < 0) {
            log.error(std::strerror(errno));
            throw connection_exception("Failed to switch to listening mode");
        }

        log.status("Listening on port ", this->port, ", press Ctrl+C to stop.");
    }

    void listener::check_sock() {
        if (this->sock < 0) {
            log.error(std::strerror(errno));
            throw connection_exception("bad socket");
        }
    }

    connection listener::next_connection() {
        log.status("Waiting for next connection...");

        check_sock();

        struct sockaddr_in client_address{};
        socklen_t client_address_len = sizeof(client_address);
        int msg_sock = accept(this->sock, (sockaddr *)(&client_address), &client_address_len);
        if (msg_sock < 0) {
            log.error(std::strerror(errno));
            throw connection_exception("Failed to accept a connection on listener socket");
        }

        log.status("Received connection");
        return connection(msg_sock);
    }

    void listener::stop() {
        log.status("Stopping listener...");

        check_sock();

        if(close(this->sock) < 0) {
            log.error("Failed to close socket ", this->sock);
        }
        log.status("Stopped");
    }
}
