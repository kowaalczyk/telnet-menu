//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_CONNECTION_H
#define TELNET_MENU_CONNECTION_H


#include "logger.h"
#include "menu.h"
#include "nvt.h"

namespace server {
    class connection {
    public:
        explicit connection(int sock);

        connection(int sock, const logger &log);

        ~connection();

        nvt create_nvt(menu m);

    private:
        logger log;
        int sock;
        bool finished;
    };
}


#endif //TELNET_MENU_CONNECTION_H
