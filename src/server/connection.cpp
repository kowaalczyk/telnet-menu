//
// Created by kowal on 21.04.18.
//

#include <zconf.h>
#include "connection.h"
#include "connection_exception.h"
#include "io.h"


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
        // Make sure client does not display the keys on its terminal


        // working send: [IAC, DO, LINEMODE, IAC, WILL, ECHO]
        // [255, 253, 34, 255, 251, 1]
        io::set_mode(this->sock);

        // send [IAC, DO, MODE, CHARACTER]
        // expect [IAC, WILL, MODE, CHARACTER] ==> OK, go on
        // if not ==> throw exception and exit
    }

    menu connection::create_menu(std::vector<std::string> options, size_t finishing_option) {
        return menu(this->sock, std::move(options), finishing_option);
    }
}
