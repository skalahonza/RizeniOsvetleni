//
// Created by skala on 17.5.17.
//

#include <iostream>
#include "Broadcaster.h"
#include "global_const.h"
#include "StateMessage.h"

Broadcaster::Broadcaster() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        errno_abort("socket init failed");
    }

    memset(&braddr, 0, sizeof(braddr));
    braddr.sin_family = AF_INET;
    braddr.sin_port = htons(DEFAULT_PORT);
    braddr.sin_addr.s_addr = INADDR_BROADCAST;

    int broadcast = 1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                   sizeof broadcast) == -1) {
        errno_abort("setsockopt (SO_BROADCAST)");
    }
}

void Broadcaster::errno_abort(const char *header) {
    perror(header);
    exit(EXIT_FAILURE);
}

void Broadcaster::broadcastData(char *data, int len) {
    socklen_t sinlen = sizeof(braddr);
    sendto(sockfd, data, (size_t) len, 0, (struct sockaddr *) &braddr, sinlen);
}

void Broadcaster::broadcastData(LightUnit unit) {
    std::cout << "Broadcasting: " << unit.broadcstDebugString() << "\n";
    StateMessage message = StateMessage(unit);
    std::vector<char> buffer = message.buildPaketBUffer();
    broadcastData(buffer.data(), (int) buffer.size());
}
