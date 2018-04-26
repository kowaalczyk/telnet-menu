//
// Created by kowal on 22.04.18.
//

#include "menu.h"
#include "menu_exception.h"
#include "io.h"
#include <utility>


namespace server {

    menu::menu(std::vector<std::string> options, size_t finishing_option) :
            options{std::move(options)},
            finishing_option{finishing_option},
            current_option{0},
            selected{false},
            selected_finishing_option{false} {}

    menu::menu(std::vector<std::string> options, size_t finishing_option, size_t starting_option) :
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

    bool menu::is_selected() const {
        return this->selected;
    }

    bool menu::selected_finish() const {
        return this->selected && this->selected_finishing_option;
    }

    std::string menu::selected_option() const {
        if (!this->selected) {
            throw menu_exception("menu is not selected");
        }
        return this->options[this->current_option];
    }

    std::vector<std::string> menu::sendable_options() {
        std::vector<std::string> ans;

        for (size_t i = 0; i < this->options.size(); i++) {
            if (i == this->current_option) {
                std::string selected_option = "* " + this->options[i];
                ans.push_back(selected_option);
            } else {
                ans.push_back(this->options[i]);
            }
        }
        return std::move(ans);
    }

    menu::menu(const menu &other) :
            options{other.options},
            finishing_option{other.finishing_option},
            current_option{0},
            selected{false},
            selected_finishing_option{false} {}

    void menu::reset_selection() {
        this->selected = false;
        this->selected_finishing_option = false;
    }
}
