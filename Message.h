//
// Created by skala on 16.5.17.
//

#ifndef UDPTASK_MESSAGE_H
#define UDPTASK_MESSAGE_H

#define PROTOCOL_VER 0x00010000


#include <inttypes.h>
#include <vector>

enum MessageType {
    STATE,
    CORRECTION,
    INVALID
};

class Message {
public:
    Message(uint32_t ALC1_, uint32_t MessageType_);

    Message(uint32_t ALC1_, uint32_t ProtVEr_, uint32_t MessageType_);

    static MessageType GetMessageType(char *buffer, int len);

    virtual std::vector<char> buildPaketBUffer();

private:
    uint32_t ALC1_;
    uint32_t ProtVEr_;
    uint32_t MessageType_;

    void SerializeUINT32(uint32_t number, std::vector<char> &buffer);

    static uint32_t DeserializeUINT32(char *data);
};


#endif //UDPTASK_MESSAGE_H
