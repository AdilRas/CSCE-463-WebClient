//
// Created by Adil Rasiyani on 2/8/23.
//

#ifndef DRAGONOV_SOCKET_H
#define DRAGONOV_SOCKET_H

#define THRESHOLD 2048
#define INITIAL_BUF_SIZE 8192

class Socket {
public:
    Socket();
    bool Read();
private:
    void ExpandBuffer();
    int socket_fd;          // socket handle
    char* buf;              // buffer
    int allocatedSize;      // size of buffer
    int currPos;            // position in the buffer
};



#endif //DRAGONOV_SOCKET_H
