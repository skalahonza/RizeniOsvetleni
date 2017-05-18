//
// Created by skala on 16.5.17.
//

#ifndef UDPTASK_LIGHTUNIT_H
#define UDPTASK_LIGHTUNIT_H


#include <inttypes.h>
#include <stdio.h>
#include <string>
#include "Color.h"

class LightUnit {
public:

    LightUnit();
    /**
     * Create instance of light control unit
     * @param ALC1 Unit Id
     * @param label Unit description max length - 16 characters
     */
    LightUnit(uint32_t ALC1, std::string label);

    uint32_t getALC1_() const;

    const std::string &getLabel_() const;

    const Color &getCeil_() const;

    void setCeil_(const Color &ceil_);

    const Color &getWall_() const;

    void setWall_(const Color &wall_);

    const uint16_t *getIcon() const;

    std::string debugString() const;

    bool isIsHost() const;

    void setIsHost(bool isHost);

    std::string broadcstDebugString() const;

    void setIcon(uint16_t icon[256]);

    void Update(const LightUnit &unit);

private:
    uint32_t ALC1_;
    std::string label_;
    Color ceil_;
    Color wall_;
    uint16_t icon_[256];
    bool isHost;
};


#endif //UDPTASK_LIGHTUNIT_H
