//
// Created by kowal on 22.04.18.
//

#include "menu.h"
#include <utility>



void server::menu::select_up() {
    if(this->selected) {
        // TODO: Exception
    }
    this->current_option = (this->current_option + 1) % this->options.size();
}

void server::menu::select_down() {
    if(this->selected) {
        // TODO: Exception
    }
    this->current_option = this->current_option > 0 ?
                           this->current_option - 1 :
                           this->options.size() - 1;
}

void server::menu::select(size_t option) {
    if(option >= this->options.size()) {
        // TODO: Exception
    }
    this->current_option = option;
}

void server::menu::interact() {
    // TODO: Clear content, send menu and read buffer
}

bool server::menu::is_selected() {
    return this->selected;
}

bool server::menu::selected_finish() {
    return this->selected && this->selected_finishing_option;
}

std::string server::menu::selected_option() {
    if (!this->selected || this->selected_finishing_option) {
        // TODO: exception
    }
    return this->options[this->current_option];
}

void server::menu::send_selected_option() {
    // TODO
}

server::menu::menu(int fd, std::vector<std::string> options, size_t finishing_option) :
        fd{fd},
        options{std::move(options)},
        finishing_option{finishing_option},
        current_option{0} {}

server::menu::menu(int fd, std::vector<std::string> options, size_t finishing_option, size_t starting_option) :
        fd{fd},
        options{std::move(options)},
        finishing_option{finishing_option},
        current_option{starting_option} {}
