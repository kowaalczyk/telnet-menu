#include <iostream>
#include <zconf.h>
#include <sstream>
#include <csignal>
#include "server/listener.h"
#include "server/menu.h"
#include "server/logger.h"
#include "server/connection_exception.h"
#include "server/menu_exception.h"
#include "server/io_exception.h"


server::listener srv;


void sig_handler(int signal) {
    (void) signal;
    srv.stop();
    exit(0); // this is a standard way to exit
}


int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 2) {
        std::cout << "USAGE: ./server PORT" << std::endl;
        exit(1);
    }

    // prepare for server creation
    server::logger log{"SERVER"};
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

    server::menu main_menu{menu_options, 2};

    std::vector<std::string> submenu_options{};
    submenu_options.emplace_back("Opcja B1");
    submenu_options.emplace_back("Opcja B2");
    submenu_options.emplace_back("Wstecz");

    server::menu sub_menu{submenu_options, 2};

    while (true) {
        try {
            server::connection c = srv.next_connection();
            server::nvt terminal = c.create_nvt(main_menu);

            while (!terminal.get_menu().selected_finish()) {
                terminal.interact();

                if (terminal.get_menu().is_selected() && terminal.get_menu().selected_option() == "Opcja B") {
                    terminal.set_menu(sub_menu);
                    while (!terminal.get_menu().selected_finish()) {
                        terminal.interact();
                    }
                    terminal.set_menu(main_menu);
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
        } catch (server::io_exception &e) {
            log.error(e.what());
            log.status("Connection exception: moving to next connection");
        }
    }
    srv.stop();
    return 0;
}
