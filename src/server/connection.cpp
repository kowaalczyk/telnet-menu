//
// Created by kowal on 21.04.18.
//

#include <zconf.h>
#include "connection.h"
#include "connection_exception.h"


namespace server {

    connection::connection(int sock) : log{"SERVER CONNECTION"}, sock{sock}, finished{false} {
        log.status("Created on socket ", this->sock);
    }

    connection::connection(int sock, const logger &log) : log{log}, sock{sock}, finished{false} {
        log.status("Created on socket ", this->sock);
    }

    connection::~connection() {
        if(close(this->sock) < 0) {
            log.error("Failed to close socket ", this->sock);
        } else {
            log.status("Closed socket ", this->sock);
        }
    }

    void connection::select() {
        this->finished = true;
    }

    bool connection::is_finished() const {
        return finished;
    }
}
