//
// Created by Adil Rasiyani on 2/8/23.
//

#include "Socket.h"
#include <sys/socket.h>
#include <poll.h>
#include <cerrno>
#include <iostream>

Socket::Socket() {
    // 0 here tells socket() to pick the default protocol appropriate for the requested socket type
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    buf = new char[INITIAL_BUF_SIZE];
    currPos = 0;
    allocatedSize = INITIAL_BUF_SIZE;
}

void Socket::ExpandBuffer() {
    char* newBuf = new char[2*allocatedSize];
    memcpy(newBuf, buf, allocatedSize);
    delete [] buf;
    buf = newBuf;
    allocatedSize = 2*allocatedSize;
}

void printErrors() {
    // TODO: Error printing
    // bad file descriptor
    if (errno == EBADF) {

    }

    // socket is non-blocking, recv would block.
    if (errno == EAGAIN or errno == EWOULDBLOCK) {

    }

    // emote host refused to allow the network connection
    if (errno == ECONNREFUSED) {

    }

    // receive buffer pointer outside process's memory space
    if (errno == EFAULT) {

    }

    // interrupted by signal before completion
    if (errno == EINTR) {

    }

    // invalid argument passed
    if (errno == EINVAL) {

    }

    // memory could not be allocated
    if (errno == ENOMEM) {

    }

    // socket associated with a protocol and not connected
    if (errno == ENOTCONN) {

    }

    // fd is not a socket
    if (errno == ENOTSOCK) {

    }

    std::cout << strerror(errno) << std::endl;
}

bool Socket::Read() {
    int ret = 0;
    const int TIMEOUT = 1000 * 10;
    pollfd fd {socket_fd, POLLIN};
    while (true) {
        ret = poll(&fd, 1, TIMEOUT);
        if (ret > 0) {
            ssize_t bytes = recv(socket_fd, buf + currPos, std::min(2*THRESHOLD, allocatedSize - currPos), 0);
            // check for errors
            if (bytes == -1) {
                printErrors();
                break;
            }

            // connection closed
            if (bytes == 0) {
                buf[0] = '\0';
                break;
            }

            currPos += (int)bytes;

            if (allocatedSize - currPos < THRESHOLD) {
                ExpandBuffer();
            }
        } else if (ret == 0) {
            // print timeout
            break;
        } else {
            // print errors
            break;
        }
        break;
    }
    return false;
}