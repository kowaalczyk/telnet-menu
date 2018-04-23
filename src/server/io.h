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
    private:
        static void standard_response(int fd, const std::string &request_buffer);

        static key read_arrow(const std::string &buffer, ssize_t buffer_len);

        static key read_return(const std::string &buffer, ssize_t buffer_len);

    public:
        static key read_key(int fd);

        static void display_lines(int fd, std::vector<std::string> txt);

        static void append_line(int fd, const std::string &line);
    };
}


#endif //TELNET_MENU_IO_H
