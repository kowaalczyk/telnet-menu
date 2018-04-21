//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_CONNECTION_H
#define TELNET_MENU_CONNECTION_H


#include <exception>
#include <cstring>
#include <string>
#include <utility>

namespace server {
    static const int QUEUE_SIZE = 10;

    class connection {
    private:
        unsigned int port;
        int sock;
        struct sockaddr_in server_address;

    public:
        explicit connection(unsigned int port);
    };

    class connection_exception : public std::exception {
    private:
        const std::string message{};

    public:
        explicit connection_exception(std::string message) : message(std::move(message)) {};

        const char *what() const noexcept override;
    };
}


#endif //TELNET_MENU_CONNECTION_H
