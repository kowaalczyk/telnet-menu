//
// Created by kowal on 22.04.18.
//

#ifndef TELNET_MENU_MENU_H
#define TELNET_MENU_MENU_H

#include <string>
#include <vector>

namespace server {
    class menu {
    private:
        std::vector<std::string> options;
        size_t finishing_option;
        size_t current_option;
        bool selected;
        bool selected_finishing_option;

    public:
        menu(std::vector<std::string> options, size_t finishing_option);
        menu(std::vector<std::string> options, size_t finishing_option, size_t starting_option);

        menu(const menu &other);

        std::vector<std::string> sendable_options();

        bool is_selected() const;

        bool selected_finish() const;

        std::string selected_option() const;

        void select_up();

        void select_confirm();

        void select_down();

        void select(size_t option);

        void reset_selection();
    };
}


#endif //TELNET_MENU_MENU_H
