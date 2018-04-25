//
// Created by kowal on 23.04.18.
//

#include <cstring>
#include "io_exception.h"

namespace server {

    const char *io_exception::what() const noexcept {
        std::string w = "IO ERROR: ";
        w.append(this->message);
        return w.c_str();
    }
}