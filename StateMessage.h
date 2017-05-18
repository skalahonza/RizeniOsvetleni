//
// Created by skala on 17.5.17.
//

#ifndef UDPTASK_STATEMESSAGE_H
#define UDPTASK_STATEMESSAGE_H


#include "Message.h"
#include "LightUnit.h"

class StateMessage : public Message {
public:
    StateMessage(LightUnit &unit);

    StateMessage(char *buf, int len);
    std::vector<char> buildPaketBUffer();

private:
    LightUnit unit_;
};


#endif //UDPTASK_STATEMESSAGE_H
