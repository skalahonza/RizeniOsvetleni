//
// Created by skala on 16.5.17.
//

#include "Message.h"


std::vector<char> Message::buildPaketBUffer() {
    std::vector<char> buffer;
    SerializeUINT32(ALC1_, buffer);
    SerializeUINT32(ProtVEr_, buffer);
    SerializeUINT32(MessageType_, buffer);
    return buffer;
}

void Message::SerializeUINT32(uint32_t number, std::vector<char> &buffer) {
    char *ptr = reinterpret_cast<char *>(&number);
    for (int i = 0; i < 4; i++)
        buffer.push_back(ptr[i]);
}

uint32_t Message::DeserializeUINT32(char data[4]) {
    uint32_t result;
    char *ptr = reinterpret_cast<char *>(&result);
    for (int i = 0; i < 4; i++)
        ptr[i] = data[i];
    return result;
}

MessageType Message::GetMessageType(char *buffer, int len) {
    //if (len < 8 + 4) return INVALID;

    if (len != 24)
        if (len != 548)
            return INVALID;

    switch (DeserializeUINT32(buffer + 8)) {
        case 0:
            return STATE;
        case 1:
            return CORRECTION;
        default:
            return INVALID;
    }
}

Message::Message(LightUnit unit, uint32_t protVer, uint32_t messageType) {
    ALC1_ = unit.getALC1_();
    ProtVEr_ = protVer;
    MessageType_ = messageType;
}

Message::Message(LightUnit unit, uint32_t messageType) : Message(unit, PROTOCOL_VER, messageType) {
}

Message::Message(char *buffer, int len) {
    ALC1_ = DeserializeUINT32(buffer);
    ProtVEr_ = DeserializeUINT32(buffer + 4);
    MessageType_ = DeserializeUINT32(buffer + 4);
}

void Message::SerializeUINT16(uint16_t number, std::vector<char> &buffer) {
    char *ptr = reinterpret_cast<char *>(&number);
    for (int i = 0; i < 2; i++)
        buffer.push_back(ptr[i]);
}

uint16_t Message::DeserializeUINT16(char *data) {
    uint16_t result;
    char *ptr = reinterpret_cast<char *>(&result);
    for (int i = 0; i < 2; i++)
        ptr[i] = data[i];
    return result;
}
