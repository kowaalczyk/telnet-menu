//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_LISTENER_H
#define TELNET_MENU_LISTENER_H


#include <exception>
#include <cstring>
#include <string>
#include <utility>
#include <netinet/in.h>
#include "connection.h"
#include "logger.h"

namespace server {
    static const int QUEUE_SIZE = 5;

    class listener {
    public:
        listener();

        explicit listener(unsigned int port);

        connection next_connection();

        void stop();

    private:
        unsigned int port;
        int sock;
        struct sockaddr_in server_address;
        logger log;

        void check_sock();
    };
}


#endif //TELNET_MENU_LISTENER_H
