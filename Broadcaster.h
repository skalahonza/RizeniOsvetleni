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
#include "Message.h"


class Broadcaster {
private:
    Broadcaster();
    Broadcaster(Broadcaster const &); // Don't Implement
    void operator=(Broadcaster const &); // Don't implement
    void errno_abort(const char *header);
    sockaddr_in braddr;
    int sockfd;

public:
    /**
    * Get singleton instance or create a new one
    * @return Broadcaster singleton instance
    */
    static Broadcaster &getInstance() {
        static Broadcaster INSTANCE;
        return INSTANCE;
    }

    /**
     * Broadcasts given buffer to all listeners in LAN
     * @param data Raw bytes data
     * @param len BUffer length
     */
    void broadcastData(char *data, int len);

    /**
     * Broadcasts given unit information to all listeners in LAN
     * @param unit LightUnit to be broadcaster
     */
    void broadcastData(LightUnit unit);

    /**
     * Broadcast given message to all listeners in LAN
     * @param message Message to be broadcasted
     */
    void broadcastData(Message *message);
};


#endif //UDPTASK_BROADCASTER_H
