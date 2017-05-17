//
// Created by skala on 16.5.17.
//

#ifndef UDPTASK_MESSAGE_H
#define UDPTASK_MESSAGE_H

#define PROTOCOL_VER 0x00010000


#include <inttypes.h>
#include <vector>
#include "LightUnit.h"

enum MessageType {
    STATE,
    CORRECTION,
    INVALID
};

class Message {
public:
    Message(LightUnit unit, uint32_t messageType);

    Message(LightUnit unit, uint32_t protVer, uint32_t messageType);

    static MessageType GetMessageType(char *buffer, int len);

    virtual std::vector<char> buildPaketBUffer();

private:
    uint32_t ProtVEr_;
    uint32_t MessageType_;

protected:
    LightUnit unit_;
    void SerializeUINT32(uint32_t number, std::vector<char> &buffer);
    static uint32_t DeserializeUINT32(char *data);
};


#endif //UDPTASK_MESSAGE_H
