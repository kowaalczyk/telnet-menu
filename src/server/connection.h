//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_CONNECTION_H
#define TELNET_MENU_CONNECTION_H


#include "logger.h"

namespace server {
    class connection {
    private:
        logger log;
        int sock;

    public:
        explicit connection(int sock);
        connection(int sock, const logger &log);
        ~connection();
    };
}


#endif //TELNET_MENU_CONNECTION_H
