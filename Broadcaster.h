//
// Created by skala on 17.5.17.
//

#ifndef UDPTASK_BROADCASTER_H
#define UDPTASK_BROADCASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "LightUnit.h"


class Broadcaster {
private:
    Broadcaster();
    Broadcaster(Broadcaster const &); // Don't Implement
    void operator=(Broadcaster const &); // Don't implement
    void errno_abort(const char *header);
    sockaddr_in braddr;
    int sockfd;

public:
    static Broadcaster &getInstance() {
        static Broadcaster INSTANCE;
        return INSTANCE;
    }

    void broadcastData(char *data, int len);

    void broadcastData(volatile LightUnit unit);
};


#endif //UDPTASK_BROADCASTER_H
