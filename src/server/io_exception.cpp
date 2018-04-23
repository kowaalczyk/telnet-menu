//
// Created by kowal on 23.04.18.
//

#include <cstring>
#include "io_exception.h"

namespace server {

    const char *io_exception::what() const noexcept {
        return strcat(const_cast<char *>("IO ERROR: "), message.c_str());
    }
}