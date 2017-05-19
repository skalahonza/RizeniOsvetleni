//
// Created by Jan Skála on 25.04.2017.
//

#ifndef UDPTASK_COMMUNICATOR_H
#define UDPTASK_COMMUNICATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "global_const.h"
#include "LightUnit.h"
#include "UpdateMessage.h"

class Updater {
public:
    Updater(LightUnit unit);

    void sendUpdate();

private:
    void errno_abort(const char *header);

    sockaddr_in braddr;
    int sockfd;
    UpdateMessage message_;
};


#endif //UDPTASK_COMMUNICATOR_H
