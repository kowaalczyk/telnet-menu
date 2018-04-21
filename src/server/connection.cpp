//
// Created by kowal on 21.04.18.
//

#include <zconf.h>
#include "connection.h"
#include "connection_exception.h"


namespace server {

    connection::connection(int sock) : sock{sock} {}

    connection::~connection() {
        if(close(this->sock) < 0) {
            log.error("Failed to close server socket ", this->sock);
        }
    }

    connection::connection(int sock, const logger &log) : log{log}, sock{sock} {}
}
