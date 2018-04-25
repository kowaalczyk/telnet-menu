//
// Created by kowal on 22.04.18.
//

#include "menu.h"
#include "menu_exception.h"
#include "io.h"
#include <utility>


namespace server {
    menu::menu(int fd, std::vector<std::string> options, size_t finishing_option) :
            fd{fd},
            options{std::move(options)},
            finishing_option{finishing_option},
            current_option{0},
            selected{false},
            selected_finishing_option{false} {}

    menu::menu(int fd, std::vector<std::string> options, size_t finishing_option, size_t starting_option) :
            fd{fd},
            options{std::move(options)},
            finishing_option{finishing_option},
            current_option{starting_option},
            selected{false},
            selected_finishing_option{false} {}

    void menu::select_up() {
        if (this->selected) {
            throw menu_exception("cannot change selection in menu that was already selected");
        }
        this->current_option = (this->current_option + 1) % this->options.size();
    }

    void menu::select_down() {
        if (this->selected) {
            throw menu_exception("cannot change selection in menu that was already selected");
        }
        this->current_option = this->current_option > 0 ?
                               this->current_option - 1 :
                               this->options.size() - 1;
    }

    void menu::select_confirm() {
        if (this->selected) {
            throw menu_exception("selection already confirmed");
        }
        this->selected = true;
        this->selected_finishing_option = (this->current_option == this->finishing_option);
    }

    void menu::select(size_t option) {
        if (option >= this->options.size()) {
            throw menu_exception("attempting to select an option that does not exist");
        }
        this->current_option = option;
    }

    void menu::interact() {
        io::display_lines(this->fd, this->sendable_options());
        key msg = io::read_key(this->fd);

        switch (msg) {
            case ARROW_UP:
                this->select_up();
                break;
            case ARROW_DOWN:
                this->select_down();
                break;
            case RETURN:
                this->select_confirm();
                break;
            default:
                // ignore
                break;
        }
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
        io::append_line(this->fd, this->selected_option());
    }

    std::vector<std::string> menu::sendable_options() {
        std::vector<std::string> ans;

        for (size_t i = 0; i < this->options.size(); i++) {
            if (i == this->current_option) {
                std::string selected_option = "* " +  this->options[i];
                ans.push_back(selected_option);
            } else {
                ans.push_back(this->options[i]);
            }
        }
        return std::move(ans);
    }
}
