//
// Created by skala on 16.5.17.
//

#ifndef UDPTASK_LIGHTUNIT_H
#define UDPTASK_LIGHTUNIT_H

#include <inttypes.h>
#include <stdio.h>
#include <string>
#include "Color.h"
#include "global_const.h"

class LightUnit {
public:

    LightUnit();
    /**
     * Create instance of light control unit
     * @param ALC1 Unit Id
     * @param label Unit description max length - 16 characters
     */
    LightUnit(uint32_t ALC1, std::string label);

    /**
     * Create instance of light control unit, used for sending
     * @param ip IP address of the unit
     * @param label Name of the unit
     */
    LightUnit(std::string ip, std::string label);

    uint32_t getALC1_() const;

    const std::string &getLabel_() const;

    const Color &getCeil_() const;

    void setCeil_(const Color &ceil_);

    const Color &getWall_() const;

    void setWall_(const Color &wall_);

    const uint16_t *getIcon() const;

    std::string debugString() const;

    std::string broadcstDebugString() const;

    void setIcon(uint16_t icon[256]);

    void Update(const LightUnit &unit);

    std::string getIp()const;

    bool isIsHost_() const;

    void setIsHost_(bool isHost_);

    bool isIdle();

    void resetIdle();

    void incrementIdle();

private:
    uint32_t ALC1_;
    std::string label_;
    Color ceil_;
    Color wall_;
    uint16_t icon_[256];
    bool isHost_;
    int idle_timeout = DEFAULT_DILE_TIMEOUT;
};


#endif //UDPTASK_LIGHTUNIT_H
