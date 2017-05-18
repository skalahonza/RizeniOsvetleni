//
// Created by skala on 16.5.17.
//

#include <sstream>
#include <cstring>
#include "LightUnit.h"
#include "StateMessage.h"
#include "NetTools.h"

LightUnit::LightUnit(uint32_t ALC1, std::string label) :
        ALC1_(ALC1), label_(label), isHost(false) {
    wall_ = Color();
    ceil_ = Color();
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
    return icon_;
}

uint32_t LightUnit::getALC1_() const {
    return ALC1_;
}

const std::string &LightUnit::getLabel_() const {
    return label_;
}

std::string LightUnit::debugString() const {
    std::stringstream stream;
    stream << "ID: " << ALC1_ << " Label: " << label_;
    return stream.str();
}

std::string LightUnit::broadcstDebugString() const {
    std::stringstream stream;
    stream << debugString();
    char data[100] = {0};
    sprintf(data, " Wall(%d,%d,%d) Ceil(%d,%d,%d)", wall_.getRGB888().r, wall_.getRGB888().g, wall_.getRGB888().b,
            ceil_.getRGB888().r, ceil_.getRGB888().g, ceil_.getRGB888().b);
    stream << data;
    return stream.str();
}

bool LightUnit::isIsHost() const {
    return isHost;
}

void LightUnit::setIsHost(bool isHost) {
    LightUnit::isHost = isHost;
}

LightUnit::LightUnit() : LightUnit(0, "") {
}

void LightUnit::setIcon(uint16_t icon[256]) {
    for (int i = 0; i < 256; ++i) {
        icon_[i] = icon[i];
    }
}

void LightUnit::Update(const LightUnit &unit) {
    ceil_ = unit.getCeil_();
    wall_ = unit.getWall_();
}

std::string LightUnit::getIp() {
    return NetTools::fromUINT32(ALC1_);
}

LightUnit::LightUnit(std::string ip, std::string label)
        : LightUnit(NetTools::toUINT32(ip), label) {
}
