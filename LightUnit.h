//
// Created by skala on 16.5.17.
//

#ifndef UDPTASK_LIGHTUNIT_H
#define UDPTASK_LIGHTUNIT_H


#include <cstdint>
#include "Color.h"

class LightUnit {
public:
    LightUnit(uint32_t ALC1, const char label[16]);

    uint32_t getALC1_() const;

    const char *getLabel_() const;

    const Color &getCeil_() const;

    void setCeil_(const Color &ceil_);

    const Color &getWall_() const;

    void setWall_(const Color &wall_);

    const uint16_t *getIcon() const;

private:
    uint32_t ALC1_;
    const char label_[16];
    Color ceil_;
    Color wall_;
    uint16_t icon[256];
};


#endif //UDPTASK_LIGHTUNIT_H
