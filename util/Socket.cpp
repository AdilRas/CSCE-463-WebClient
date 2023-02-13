//
// Created by Adil Rasiyani on 2/8/23.
//

#include "Socket.h"
#include <sys/socket.h>
#include <poll.h>

Socket::Socket() {
    // 0 here tells socket() to pick the default protocol appropriate for the requested socket type
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    buf = new char[256];
    curPos = 0;
    allocatedSize = 256;
}

bool Socket::Read() {
    int ret;
    const int TIMEOUT = 1000 * 10;
    pollfd fd {socket_fd, POLLIN};
    while (true) {
        if ((ret = poll(&fd, 1, TIMEOUT))) {
            ssize_t bytes = recv(socket_fd, buf + curPos, allocatedSize - curPos, 0);

        }
            break;
    }
    return true;
}