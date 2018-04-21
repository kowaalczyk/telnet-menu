#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include <sstream>
#include "server/connection.h"
#include "server/logger.h"


template<typename T>
void r_print(T t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void r_print(T t, Args... args) {
    std::cout << t;
    r_print(args...);
}


int main(int argc, char * argv[]) {
    if(argc != 2) {
        std::cout << "USAGE: ./server PORT" << std::endl;
        exit(1);
    }

    server::logger log;
    unsigned int port;
    std::istringstream ss(argv[1]);
    if(!(ss >> port) || port < 0 || port > UINT16_MAX) {
        log.error("port is not a valid integer!");
        exit(1);
    }
    log.status("starting on port ", port, "...");

    try {
        auto c = server::connection(port);
    } catch (server::connection_exception &e) {
        log.error(e.what());
    }
    log.status("listening on port ", port);



////    TODO: Setup connetcion
//
//    int sock, msg_sock;
//    struct sockaddr_in server_address;
//    struct sockaddr_in client_address;
//    socklen_t client_address_len;
//
//    char buffer[BUFFER_SIZE];
//    ssize_t len, snd_len;
//
//    sock = socket(PF_INET, SOCK_STREAM, 0); // creating IPv4 TCP socket
//    if (sock < 0)
//        syserr("socket");
//    // after socket() call; we should close(sock) on any execution path;
//    // since all execution paths exit immediately, sock would be closed when program terminates
//
//    server_address.sin_family = AF_INET; // IPv4
//    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // listening on all interfaces
//    server_address.sin_port = htons(PORT_NUM); // listening on port PORT_NUM
//
//    // bind the socket to a concrete address
//    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
//        syserr("bind");
//
//    // switch to listening (passive open)
//    if (listen(sock, QUEUE_LENGTH) < 0)
//        syserr("listen");
//
//    printf("accepting client connections on port %hu\n", ntohs(server_address.sin_port));
//    for (;;) {
//        client_address_len = sizeof(client_address);
//        // get client connection from the socket
//        msg_sock = accept(sock, (struct sockaddr *) &client_address, &client_address_len);
//        if (msg_sock < 0)
//            syserr("accept");
//        do {
//            len = read(msg_sock, buffer, sizeof(buffer));
//            if (len < 0)
//                syserr("reading from client socket");
//            else {
//                printf("read from socket: %zd bytes: %.*s\n", len, (int) len, buffer);
//                snd_len = write(msg_sock, buffer, len);
//                if (snd_len != len)
//                    syserr("writing to client socket");
//            }
//        } while (len > 0);
//        printf("ending connection\n");
//        if (close(msg_sock) < 0)
//            syserr("close");
//    }
//
//
//    TODO: Handle each incoming message via telnet client

    return 0;
}
