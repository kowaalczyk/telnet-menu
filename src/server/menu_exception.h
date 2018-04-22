//
// Created by kowal on 22.04.18.
//

#ifndef TELNET_MENU_MENU_EXCEPTION_H
#define TELNET_MENU_MENU_EXCEPTION_H


#include <string>

namespace server {
    class menu_exception : public std::exception {
    private:
        const std::string message{};

    public:
        explicit menu_exception(std::string message) : message(std::move(message)) {};

        const char *what() const noexcept override;
    };
}


#endif //TELNET_MENU_MENU_EXCEPTION_H
