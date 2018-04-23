#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include <sstream>
#include <csignal>
#include "server/listener.h"
#include "server/logger.h"
#include "server/connection_exception.h"
#include "server/menu.h"
#include "server/menu_exception.h"


server::listener srv;


void sig_handler(int signal) {
    (void) signal;
    srv.stop();
    exit(0); // this is a standard way to exit
}


int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 2) {
        std::cout << "USAGE: ./listener PORT" << std::endl;
        exit(1);
    }

    // prepare for server creation
    server::logger log;
    unsigned int port;
    std::istringstream ss(argv[1]);
    if (!(ss >> port) || port > UINT16_MAX) {
        log.error(argv[1], " is not a valid port number");
        exit(1);
    }

    // start server
    try {
        srv = server::listener(port);
    } catch (server::connection_exception &e) {
        log.error(e.what());
        exit(1);
    }

    // allow to end the server
    std::signal(SIGINT, sig_handler);

    // prepare menu content
    std::vector<std::string> menu_options{};
    menu_options.emplace_back("Opcja A");
    menu_options.emplace_back("Opcja B");
    menu_options.emplace_back("Koniec");

    std::vector<std::string> submenu_options{};
    submenu_options.emplace_back("Opcja B1");
    submenu_options.emplace_back("Opcja B2");
    submenu_options.emplace_back("Wstecz");

    size_t menu_exit_option_idx = 2;

    // process connections
    while (true) {
        try {
            server::connection c = srv.next_connection();
            c.set_up();

            server::menu m = c.create_menu(menu_options, menu_exit_option_idx);
            while(!m.selected_finish()) {
                while (!m.is_selected()) {
                    m.interact();
                }

                if (m.selected_option() == "Opcja B") {
                    server::menu sub = c.create_menu(submenu_options, menu_exit_option_idx);
                    while(!sub.selected_finish()) {
                        while (!sub.is_selected()) {
                            sub.interact();
                        }

                        if (!sub.selected_finish()) {
                            sub.send_selected_option();
                        }
                    }
                } else if(!m.selected_finish()) {
                    m.send_selected_option();
                }
            }
        } catch (server::menu_exception &e) {
            // this can happen only due to serious logic mistake
            log.error(e.what());
            srv.stop();
            exit(1);
        } catch (server::connection_exception &e) {
            log.error(e.what());
            log.status("Connection exception: moving to next connection");
        }
    }

//            len = read(msg_sock, buffer, sizeof(buffer));
//            if (len < 0)
//                syserr("reading from client socket");
//            else {
//                printf("read from socket: %zd bytes: %.*s\n", len, (int) len, buffer);
//                snd_len = write(msg_sock, buffer, len);
//                if (snd_len != len)
//                    syserr("writing to client socket");
//            }

    srv.stop();
    return 0;
}
