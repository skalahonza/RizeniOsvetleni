//
// Created by skala on 18.5.17.
//

#ifndef UDPTASK_LISTENER_H
#define UDPTASK_LISTENER_H

#include "StateMessage.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

typedef void (*t_status_rec_callback)(StateMessage);

typedef void (*t_invalid_message_callback)();

class Listener {
public:
    Listener(t_status_rec_callback status_Rrceived_, t_invalid_message_callback invalid_message_);

    void startListening();

    void stopListening();

private:
    void listeningLoop();
    volatile bool loop_;
    int sockfd_;
    struct sockaddr_in bindaddr_;
    struct sockaddr_in si_other_;

    //Callbacks
    t_status_rec_callback status_Rrceived_;
    t_invalid_message_callback invalid_message_;
};


#endif //UDPTASK_LISTENER_H
