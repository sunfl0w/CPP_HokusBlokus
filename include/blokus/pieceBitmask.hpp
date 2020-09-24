#pragma once

#include <bitset>

#include "vec2ui.hpp"
#include "maskType.hpp"

namespace HokusBlokus::Blokus {
    class PieceBitmask {
    private:
        std::bitset<484> bitmask;
        Vec2ui maskDimensions;
        MaskType maskType;

    public:
        PieceBitmask(std::bitset<484> bitmask, MaskType maskType);

        const std::bitset<484>& GetBitmask() const;

        const Vec2ui& GetMaskDimensions() const;
        
        MaskType GetMaskType() const;

        bool operator==(const PieceBitmask& other);

    private:
        Vec2ui ComputeMaskDimensions(const std::bitset<484>& bitmask) const;
    };
}