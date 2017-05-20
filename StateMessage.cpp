//
// Created by skala on 17.5.17.
//

#include "StateMessage.h"

StateMessage::StateMessage(LightUnit &unit) : Message(unit, 0) {
    unit_ = unit;
}

std::vector<char> StateMessage::buildPaketBUffer() {
    std::vector<char> buffer = Message::buildPaketBUffer();
    Message::SerializeUINT32(unit_.getCeil_().toUINT32(), buffer);
    Message::SerializeUINT32(unit_.getWall_().toUINT32(), buffer);

    //add label
    for (int i = 0; i < 16; ++i) {
        if (i > unit_.getLabel_().length() - 1)
            buffer.push_back('\0');
        else
            buffer.push_back(unit_.getLabel_()[i]);
    }

    //Add icon
    for (int j = 0; j < 256; ++j) {
        uint16_t a = unit_.getIcon()[j];
        SerializeUINT16(a, buffer);
    }

    return buffer;
}

StateMessage::StateMessage(char *buf, int len) : Message(buf, len) {
    uint32_t ceil = 0;
    uint32_t wall = 0;
    char label[16] = {0};
    uint16_t icon[256] = {0};

    if (len > 12)
        ceil = DeserializeUINT32(buf + 12);

    if (len > 16)
        wall = DeserializeUINT32(buf + 16);

    //deserialize label
    if (len > 36)
        for (int i = 0; i < 16; ++i) {
            label[i] = buf[20 + i];
        }

    //deserialize icon
    if (len > 36 + 256)
        for (int j = 0; j < 256; ++j) {
            icon[j] = (uint16_t) buf[36 + j];
        }

    unit_ = LightUnit(ALC1_, label);
    unit_.setWall_(Color::fromUINT32(wall));
    unit_.setCeil_(Color::fromUINT32(ceil));
    unit_.setIcon(icon);
}

const LightUnit &StateMessage::getUnit_() const {
    return unit_;
}

