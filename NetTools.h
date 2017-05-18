//
// Created by skala on 18.5.17.
//

#ifndef UDPTASK_NETTOOLS_H
#define UDPTASK_NETTOOLS_H

#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

class NetTools {
public:
    static std::string getMyIp();

    static uint32_t toUINT32(std::string ip);

    static std::string fromUINT32(uint32_t data);
};


#endif //UDPTASK_NETTOOLS_H
