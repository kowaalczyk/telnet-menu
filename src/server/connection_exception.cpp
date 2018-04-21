//
// Created by kowal on 21.04.18.
//

#include "connection_exception.h"


namespace server {
    const char * connection_exception::what() const noexcept {
        return strcat(const_cast<char *>("CONNECTION ERROR: "), message.c_str());
    }
}
