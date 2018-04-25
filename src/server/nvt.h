//
// Created by kowal on 25.04.18.
//

#ifndef TELNET_MENU_NVT_H
#define TELNET_MENU_NVT_H


#include "menu.h"

namespace server {
    class nvt {
    public:
        nvt(int fd, const menu m);

        nvt(int fd, const menu &m, const std::string &msg);

        const menu &get_menu() const;

        void set_menu(const menu m);

        const std::string &get_msg() const;

        void set_msg(const std::string &msg);

        void interact();

    private:
        int fd;
        menu m;
        std::string msg;
    };
}


#endif //TELNET_MENU_NVT_H
