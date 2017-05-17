//
// Created by skala on 17.5.17.
//

#include "StateMessage.h"

StateMessage::StateMessage(LightUnit &unit) : Message(unit, 0) {
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

    //TODO Add icon
    for (int j = 0; j < 512; ++j) {
        buffer.push_back('\0');
    }

    return buffer;
}

