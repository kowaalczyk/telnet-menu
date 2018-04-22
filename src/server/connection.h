//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_CONNECTION_H
#define TELNET_MENU_CONNECTION_H


#include "logger.h"
#include "menu.h"

namespace server {
    class connection {
    private:
        logger log;
        int sock;
        bool finished;

    public:
        explicit connection(int sock);
        connection(int sock, const logger &log);
        ~connection();

        void set_up();

        menu create_menu(std::vector<std::string> options, size_t finishing_option);
    };
}


#endif //TELNET_MENU_CONNECTION_H
