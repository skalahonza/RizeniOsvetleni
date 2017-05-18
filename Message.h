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
protected:
    Message(LightUnit unit, uint32_t messageType);

    Message(LightUnit unit, uint32_t protVer, uint32_t messageType);

    Message(char *buffer, int len);

public:
    static MessageType GetMessageType(char *buffer, int len);

    virtual std::vector<char> buildPaketBUffer();

protected:
    uint32_t ALC1_;
    uint32_t ProtVEr_;
    uint32_t MessageType_;
    void SerializeUINT32(uint32_t number, std::vector<char> &buffer);
    static uint32_t DeserializeUINT32(char *data);

    void SerializeUINT16(uint16_t number, std::vector<char> &buffer);

    static uint16_t DeserializeUINT16(char *data);
};


#endif //UDPTASK_MESSAGE_H
