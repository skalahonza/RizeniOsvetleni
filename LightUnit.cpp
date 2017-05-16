//
// Created by skala on 16.5.17.
//

#include "LightUnit.h"

LightUnit::LightUnit(uint32_t ALC1, const char label[16]) :
        ALC1_(ALC1), label_(label) {

}

const Color &LightUnit::getCeil_() const {
    return ceil_;
}

void LightUnit::setCeil_(const Color &ceil_) {
    LightUnit::ceil_ = ceil_;
}

const Color &LightUnit::getWall_() const {
    return wall_;
}

void LightUnit::setWall_(const Color &wall_) {
    LightUnit::wall_ = wall_;
}

const uint16_t *LightUnit::getIcon() const {
    return icon;
}

uint32_t LightUnit::getALC1_() const {
    return ALC1_;
}

const char *LightUnit::getLabel_() const {
    return label_;
}
