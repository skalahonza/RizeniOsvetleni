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
    /**
     * Creates instance of message and automatically serialize common data for all messages
     * @param unit LightUnit that is meant to be updated or send via broadcast
     * @param messageType 0 - for status 1 - for update
     */
    Message(LightUnit unit, uint32_t messageType);

    /**
     * Creates instance of message and automatically serialize common data for all messages
     * @param unit LightUnit that is meant to be updated or send via broadcast
     * @param protVer Protocol version, set if it differs from PROTOCOL_VER (default protocol)
     * @param messageType
     */
    Message(LightUnit unit, uint32_t protVer, uint32_t messageType);

    /**
     * Creates instance of message and automatically deserialize common received data for all messages
     * @param buffer Received buffer (raw data)
     * @param len Received buffer length
     */
    Message(char *buffer, int len);

public:
    /**
     * Analyze received buffer and validate message type
     * @param buffer Received buffer (raw bytes)
     * @param len Received buffer length
     * @return Invalid when the buffer is not like any known message type
     */
    static MessageType GetMessageType(char *buffer, int len);

    /**
     * Serialize object inner data into packet buffer
     * @return Serialized data as a byte buffer
     */
    virtual std::vector<char> buildPaketBUffer();

protected:
    uint32_t ALC1_;
    uint32_t ProtVEr_;
    uint32_t MessageType_;
    void SerializeUINT32(uint32_t number, std::vector<char> &buffer);
    static uint32_t DeserializeUINT32(char *data);

    /**
     * Serialize uint16_t number into given given buffer (adds 2 bytes)
     * @param number Number to be serialized
     * @param buffer Buffer where to add the serialized data
     */
    void SerializeUINT16(uint16_t number, std::vector<char> &buffer);

    /**
     * Deserialize uint16_t number from given buffer (deserialize first two bytes)
     * @param data Buffer to be deserialized
     * @return Deserialized number
     */
    static uint16_t DeserializeUINT16(char *data);
};


#endif //UDPTASK_MESSAGE_H
