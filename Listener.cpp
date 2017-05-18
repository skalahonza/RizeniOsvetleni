//
// Created by skala on 18.5.17.
//

#include "Listener.h"
#include "global_const.h"

Listener::Listener(t_status_rec_callback status_Rrceived_,
                   t_invalid_message_callback invalid_message_)
        : status_Rrceived_(status_Rrceived_),
          invalid_message_(invalid_message_) {

    if ((sockfd_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    memset(&bindaddr_, 0, sizeof(bindaddr_));
    bindaddr_.sin_family = AF_INET;
    bindaddr_.sin_port = htons(DEFAULT_PORT);
    bindaddr_.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd_, (struct sockaddr *) &bindaddr_, sizeof(bindaddr_)) == -1) {
        perror("binding failed\n");
        exit(1);
    }

    int yes = 1;
    if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(yes)) == -1) {
        perror("setsockopt (SO_REUSEADDR)");
        exit(1);
    }
}

void Listener::startListening() {
    loop_ = true;
    listeningLoop();
}

void Listener::stopListening() {
    loop_ = false;
}

void Listener::listeningLoop() {
    while (loop_) {
        sleep(1);
        int recv_len;
        int slen = sizeof(si_other_);
        char buf[PACKET_MAX_LEN] = {0};
        //try to receive some data, this is a blocking call
        recv_len = (int) recvfrom(sockfd_, buf, PACKET_MAX_LEN, 0, (struct sockaddr *) &si_other_, (socklen_t *) &slen);
        switch (Message::GetMessageType(buf, recv_len)) {
            case STATE: {
                StateMessage message = StateMessage(buf, recv_len);
                status_Rrceived_(message);
                break;
            }
            case CORRECTION: {
                break;
            }
            case INVALID:
                invalid_message_();
                break;
        }
    }
}
