//
// Created by Adil Rasiyani on 2/8/23.
//

#ifndef DRAGONOV_SOCKET_H
#define DRAGONOV_SOCKET_H

class Socket {
public:
    Socket();
    bool Read();
private:
    int socket_fd;         // socket handle
    char* buf;          // buffer
    int allocatedSize;  // size of buffer
    int curPos;         // position in the buffer
};



#endif //DRAGONOV_SOCKET_H
