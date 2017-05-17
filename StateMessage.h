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

    std::vector<char> buildPaketBUffer();

};


#endif //UDPTASK_STATEMESSAGE_H
