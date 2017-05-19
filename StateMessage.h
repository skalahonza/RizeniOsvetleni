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

    /**
     * Serialize object inner data into packet buffer
     * @return Serialized data as a byte buffer
     */
    std::vector<char> buildPaketBUffer();

    /**
     * Retrieve information about a unit that was passed along with the message
     * @return deserialized LightUNit object (label is empty on receive)
     */
    const LightUnit &getUnit_() const;

private:
    LightUnit unit_;
};


#endif //UDPTASK_STATEMESSAGE_H
