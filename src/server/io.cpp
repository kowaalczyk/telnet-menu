//
// Created by kowal on 23.04.18.
//

#include "io.h"

namespace server {

    void io::standard_response(int fd, const std::string &request_buffer) {
        // TODO: Standard response to incoming negotiation
    }

    key io::read_arrow(const std::string &buffer, ssize_t buffer_len) {
        if(buffer[0] != '\x1B' || buffer_len != 3 || buffer[1] != '\x5B') {
            return NOT_RECOGNIZED;
        }
        if(buffer[2] == 'A') { // arrow up == [27, 91, 65]
            return ARROW_UP;
        }
        if(buffer[2] == 'B') { // arrow down == [27, 91, 66]
            return ARROW_DOWN;
        }
        return NOT_RECOGNIZED;
    }

    key io::read_return(const std::string &buffer, ssize_t buffer_len) {
        if (buffer_len == 2 && buffer[0] == '\x0D' && buffer[1] == '\0') {
            return RETURN;
        }
        return NOT_RECOGNIZED;
    }

    key io::read_key(int fd) {
        char buffer[5];
        std::string s;

        ssize_t len = 0;
        len = read(fd, &buffer, sizeof(buffer));
        if (len < 0) {
            throw io_exception("invalid read");
        }
        if (len == 0) {
            throw io_exception("empty read"); // TODO: Should this really throw?
        }

        switch (buffer[0]) {
            case '\xFF':
                // IAC
                standard_response(fd, std::string(buffer));
                return NOT_RECOGNIZED;
            case '\x1B':
                // arrow (probably)
                return read_arrow(std::string(buffer), len);
            case '\x0D':
                // return (probably)
                return read_return(std::string(buffer), len);
            default:
                return NOT_RECOGNIZED;
        }
    }

    void io::display_lines(int fd, std::vector<std::string> txt) {
        // TODO: Flush screen - telnet FF
        // TODO: Send text
    }

    void io::append_line(int fd, const std::string &line) {
        // TODO: Send line (without flushing)
    }
}