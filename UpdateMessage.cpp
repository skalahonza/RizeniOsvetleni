//
// Created by skala on 18.5.17.
//

#include "UpdateMessage.h"

UpdateMessage::UpdateMessage(LightUnit unit) : Message(unit, 1), unit_(unit) {

}

UpdateMessage::UpdateMessage(char *buf, int len) : Message(buf, len) {
    uint16_t rc = 0;
    uint16_t gc = 0;
    uint16_t bc = 0;

    uint16_t rw = 0;
    uint16_t gw = 0;
    uint16_t bw = 0;

    if (len > 12)
        rc = DeserializeUINT16(buf + 12);

    if (len > 14)
        gc = DeserializeUINT16(buf + 14);

    if (len > 16)
        bc = DeserializeUINT16(buf + 16);

    if (len > 18)
        rw = DeserializeUINT16(buf + 18);

    if (len > 20)
        gw = DeserializeUINT16(buf + 20);

    if (len > 22)
        bw = DeserializeUINT16(buf + 22);

    unit_.setWall_(Color(rw, gw, bw));
    unit_.setCeil_(Color(rc, gc, bc));
}

std::vector<char> UpdateMessage::buildPaketBUffer() {
    std::vector<char> buffer = Message::buildPaketBUffer();
    Message::SerializeUINT16((uint16_t) unit_.getCeil_().getRGB888().r, buffer);
    Message::SerializeUINT16((uint16_t) unit_.getCeil_().getRGB888().g, buffer);
    Message::SerializeUINT16((uint16_t) unit_.getCeil_().getRGB888().b, buffer);

    Message::SerializeUINT16((uint16_t) unit_.getWall_().getRGB888().r, buffer);
    Message::SerializeUINT16((uint16_t) unit_.getWall_().getRGB888().g, buffer);
    Message::SerializeUINT16((uint16_t) unit_.getWall_().getRGB888().b, buffer);
    return buffer;
}
