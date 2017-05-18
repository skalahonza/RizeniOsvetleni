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
    /**
     * Checks local IPV4 addres and returns it
     * @return in standard fromat example: 10.20.30.40
     */
    static std::string getMyIp();

    /**
     * Serialize ipv4 addres into uint32
     * @param ip format n.n.n.n example: 10.20.30.40
     * @return SERIALIZED Ipv4 ADDRESS
     */
    static uint32_t toUINT32(std::string ip);

    /**
     * GEts IPV4 address string from uint32
     * @param data Serialized uint32 ip address
     * @return in standard format example: 10.20.30.40
     */
    static std::string fromUINT32(uint32_t data);
};


#endif //UDPTASK_NETTOOLS_H
