//
// Created by kowal on 23.04.18.
//

#include <cstring>
#include "io.h"

namespace server {

    void io::set_mode(int fd) {
        // TODO: Check if response is correct (try to force or ignore and notify)

        // [255, 253, 34, 255, 251, 1]
        char mode_codes[7] = "\377\375\042\377\373\001";
        if (write(fd, mode_codes, 6) != 6) {
            throw io_exception("invalid write: mode_codes");
        }
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
        char flush[3] = {0x1B, 'c', 0};
        if (write(fd, flush, 2) != 2) {
            throw io_exception("invalid write: flush");
        }
        for (const auto &v : txt) {
            append_line(fd, v);
        }
    }

    void io::append_line(int fd, std::string line) {
        size_t len = line.size() + 2;
        std::string line_terminated = line + "\x0D\x0A"; // TODO: Refactor to constants and check CR LF vs CR NUL
        if (write(fd, line_terminated.c_str(), len) != static_cast<ssize_t>(len)) {
            throw io_exception("invalid write: [line, CR, LF]");
        }
    }

    key io::read_arrow(const std::string &buffer, ssize_t buffer_len) {
        if (buffer[0] != '\x1B' || buffer_len != 3 || buffer[1] != '\x5B') {
            return NOT_RECOGNIZED;
        }
        if (buffer[2] == 'B') { // arrow up == [27, 91, 66]
            return ARROW_UP;
        }
        if (buffer[2] == 'A') { // arrow down == [27, 91, 65]
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
}
