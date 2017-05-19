//
// Created by skala on 18.5.17.
//

#ifndef UDPTASK_UPDATEMESSAGE_H
#define UDPTASK_UPDATEMESSAGE_H


#include "Message.h"

class UpdateMessage : public Message {
public:
    /**
     * Creates UpdateMessage instance, used in Updater class for updates over UDP
     * @param unit LightUnit that is meant to be updated
     */
    UpdateMessage(LightUnit unit);

    /**
     * Serialize received buffer into UpdateMessage object
     * @param buf received buffer
     * @param len length of received buffer
     */
    UpdateMessage(char *buf, int len);

    /**
     * Serialize object inner data into packet buffer
     * @return Serialized data as a byte buffer
     */
    virtual std::vector<char> buildPaketBUffer();

    /**
     * Retrieve information about a unit that was passed along with the message
     * @return deserialized LightUNit object (label is empty on receive)
     */
    const LightUnit &getUnit_() const;

private:
    LightUnit unit_;
};


#endif //UDPTASK_UPDATEMESSAGE_H
