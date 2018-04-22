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
        if (close(this->sock) < 0) {
            log.error("Failed to close socket ", this->sock);
        } else {
            log.status("Closed socket ", this->sock);
        }
    }

    void connection::set_up() {
        // TODO
        // Use character mode
        // Make sure flushing the screen is possible
        // Make sure background color of a line can be changed or underline added
    }

    menu connection::create_menu(std::vector<std::string> options, size_t finishing_option) {
        return menu(this->sock, std::move(options), finishing_option);
    }
}
