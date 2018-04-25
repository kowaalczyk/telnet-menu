//
// Created by kowal on 22.04.18.
//

#include <cstring>
#include "menu_exception.h"


namespace server {

    const char *menu_exception::what() const noexcept {
        std::string w = "MENU ERROR: ";
        w.append(this->message);
        return w.c_str();
    }
}