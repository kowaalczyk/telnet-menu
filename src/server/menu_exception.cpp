//
// Created by kowal on 22.04.18.
//

#include <cstring>
#include "menu_exception.h"


namespace server {

    const char *menu_exception::what() const noexcept {
        return strcat(const_cast<char *>("MENU ERROR: "), message.c_str());
    }
}