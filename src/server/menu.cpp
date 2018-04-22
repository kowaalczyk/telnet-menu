//
// Created by kowal on 22.04.18.
//

#include "menu.h"
#include "menu_exception.h"
#include <utility>


namespace server {
    menu::menu(int fd, std::vector<std::string> options, size_t finishing_option) :
            fd{fd},
            options{std::move(options)},
            finishing_option{finishing_option},
            current_option{0} {}

    menu::menu(int fd, std::vector<std::string> options, size_t finishing_option, size_t starting_option) :
            fd{fd},
            options{std::move(options)},
            finishing_option{finishing_option},
            current_option{starting_option} {}

    void menu::select_up() {
        if(this->selected) {
            throw menu_exception("cannot change selection in menu that was already selected");
        }
        this->current_option = (this->current_option + 1) % this->options.size();
    }

    void menu::select_down() {
        if(this->selected) {
            throw menu_exception("cannot change selection in menu that was already selected");
        }
        this->current_option = this->current_option > 0 ?
                               this->current_option - 1 :
                               this->options.size() - 1;
    }

    void menu::select(size_t option) {
        if(option >= this->options.size()) {
            throw menu_exception("attempting to select an option that does not exist");
        }
        this->current_option = option;
    }

    void menu::interact() {
        // TODO: Clear content, send menu and read buffer
    }

    bool menu::is_selected() {
        return this->selected;
    }

    bool menu::selected_finish() {
        return this->selected && this->selected_finishing_option;
    }

    std::string menu::selected_option() {
        if (!this->selected) {
            throw menu_exception("menu is not selected");
        }
        return this->options[this->current_option];
    }

    void menu::send_selected_option() {
        // TODO
    }
}
