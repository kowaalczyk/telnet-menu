//
// Created by kowal on 21.04.18.
//

#include "connection_exception.h"


namespace server {
    const char *connection_exception::what() const noexcept {
        std::string w = "CONNECTION ERROR: ";
        w.append(this->message);
        return w.c_str();
    }
}
