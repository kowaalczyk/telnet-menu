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
        int fd;
        std::vector<std::string> options;
        size_t finishing_option;
        size_t current_option;
        bool selected;
        bool selected_finishing_option;

        void select_up();

        void select_confirm();

        void select_down();

        void select(size_t option);

        std::vector<std::string> sendable_options();

    public:
        menu(int fd, std::vector<std::string> options, size_t finishing_option);

        menu(int fd, std::vector<std::string> options, size_t finishing_option, size_t starting_option);

        void interact();

        bool is_selected();

        bool selected_finish();

        std::string selected_option();

        void send_selected_option();
    };
}


#endif //TELNET_MENU_MENU_H
