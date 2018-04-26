//
// Created by kowal on 22.04.18.
//

#ifndef TELNET_MENU_IO_H
#define TELNET_MENU_IO_H


#include <string>
#include <zconf.h>
#include <vector>
#include "key.h"
#include "io_exception.h"

namespace server {
    class io {
    public:
        static void set_mode(int fd);

        static key read_key(int fd);

        static void display_lines(int fd, std::vector<std::string> txt);

        static void append_line(int fd, std::string line);

    private:
        static key read_arrow(const std::string &buffer, ssize_t buffer_len);

        static key read_return(const std::string &buffer, ssize_t buffer_len);
    };
}


#endif //TELNET_MENU_IO_H
