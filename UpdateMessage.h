//
// Created by skala on 18.5.17.
//

#ifndef UDPTASK_UPDATEMESSAGE_H
#define UDPTASK_UPDATEMESSAGE_H


#include "Message.h"

class UpdateMessage : public Message {
public:
    UpdateMessage(LightUnit unit);

    UpdateMessage(char *buf, int len);

    virtual std::vector<char> buildPaketBUffer();

private:
    LightUnit unit_;
};


#endif //UDPTASK_UPDATEMESSAGE_H
