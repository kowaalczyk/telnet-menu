//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_SERVER_H
#define TELNET_MENU_SERVER_H


#include <exception>
#include <cstring>
#include <string>
#include <utility>
#include "connection.h"
#include "logger.h"

namespace server {
    static const int QUEUE_SIZE = 10;

    class server {
    private:
        unsigned int port;
        int sock;
        struct sockaddr_in server_address;
        logger log;

    public:
        explicit server(unsigned int port);
        ~server();

        connection next_connection();
    };
}


#endif //TELNET_MENU_SERVER_H
