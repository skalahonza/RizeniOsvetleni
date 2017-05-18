//
// Created by skala on 18.5.17.
//

#include "NetTools.h"

std::string NetTools::getMyIp() {
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);
    char addressBuffer[INET_ADDRSTRLEN] = {0};

    //Iterate through linked list
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        } else {
            //TODO HANDLE ERROR
        }
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
    return std::string(addressBuffer);
}

uint32_t NetTools::toUINT32(std::string ip) {
    unsigned char a, b, c, d;
    sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
    return (uint32_t) (((a & 0xff) << 24) + (((b & 0xff) << 16) + ((c & 0xff) << 8) + (d & 0xff)));
}

std::string NetTools::fromUINT32(uint32_t data) {
    unsigned char a = (unsigned char) (char) (data >> 24);
    unsigned char b = (unsigned char) (char) (data >> 16);
    unsigned char c = (unsigned char) (char) (data >> 8);
    unsigned char d = (unsigned char) (data);
    char tmp[16] = {0};
    sprintf(tmp, "%d.%d.%d.%d", a, b, c, d);
    std::string result = tmp;
    return result;
}
