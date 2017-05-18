//
// Created by Jan Skála on 25.04.2017.
//

#include <arpa/inet.h>
#include "Updater.h"

Updater::Updater(LightUnit unit) : message_(unit) {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        errno_abort("socket init failed");
    }

    memset(&braddr, 0, sizeof(braddr));
    braddr.sin_family = AF_INET;
    braddr.sin_port = htons(DEFAULT_PORT);
    braddr.sin_addr.s_addr = inet_addr(unit.getIp().c_str());
}

void Updater::errno_abort(const char *header) {
    perror(header);
    exit(EXIT_FAILURE);
}

void Updater::sendUpdate() {
    std::vector<char> buffer = message_.buildPaketBUffer();
    socklen_t sinlen = sizeof(braddr);
    sendto(sockfd, buffer.data(), (size_t) buffer.size(), 0, (struct sockaddr *) &braddr, sinlen);
}
