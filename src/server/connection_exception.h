//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_CONNECTION_EXCEPTION_H
#define TELNET_MENU_CONNECTION_EXCEPTION_H


#include <string>
#include <cstring>

namespace server {
    class connection_exception : public std::exception {
    public:
        explicit connection_exception(std::string message) : message(std::move(message)) {};

        const char *what() const noexcept override;

    private:
        const std::string message{};
    };
}


#endif //TELNET_MENU_CONNECTION_EXCEPTION_H
