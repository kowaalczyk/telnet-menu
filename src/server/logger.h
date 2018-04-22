//
// Created by kowal on 21.04.18.
//

#ifndef TELNET_MENU_LOGGER_H
#define TELNET_MENU_LOGGER_H


#include <string>
#include <iostream>
#include <utility>

namespace server {
    class logger {
    private:
        std::string location;

        template<typename T>
        void r_print(T t) const {
            std::cout << t << std::endl;
        }

        template<typename T, typename... Args>
        void r_print(T t, Args... args) const {
            std::cout << t;
            r_print(args...);
        }

    public:
        logger() = default;

        explicit logger(std::string location) : location(std::move(location)) {}

        template<typename T, typename... Args>
        void error(T t, Args... args) const {
            std::cout << "[" << location << "] ERROR: ";
            r_print(t, args...);
        }

        template<typename T, typename... Args>
        void status(T t, Args... args) const {
            std::cout << "[" << location << "] STATUS: ";
            r_print(t, args...);
        }
    };
}


#endif //TELNET_MENU_LOGGER_H
