//
// Created by kowal on 25.04.18.
//

#include "nvt.h"
#include "io.h"

server::nvt::nvt(int fd, const menu m) :
        fd(fd),
        m(m),
        msg{} {}

server::nvt::nvt(int fd, const server::menu &m, const std::string &msg) :
        fd(fd),
        m(m),
        msg(msg) {}

const server::menu &server::nvt::get_menu() const {
    return m;
}

void server::nvt::set_menu(const menu m) {
    nvt::m = m;
}

const std::string &server::nvt::get_msg() const {
    return msg;
}

void server::nvt::set_msg(const std::string &msg) {
    nvt::msg = msg;
}

void server::nvt::interact() {
    std::vector<std::string> lines = this->m.sendable_options();
    lines.push_back(this->msg);

    io::display_lines(this->fd, lines);
    key msg = io::read_key(this->fd);

    switch (msg) {
        case ARROW_UP:
            this->m.select_up();
            break;
        case ARROW_DOWN:
            this->m.select_down();
            break;
        case RETURN:
            this->m.select_confirm();
            if (this->m.is_selected()) {
                this->set_msg(this->m.selected_option());
            }
            break;
        default:
            // ignore
            break;
    }
}
