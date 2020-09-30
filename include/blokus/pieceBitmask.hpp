#pragma once

#include <bitset>

#include "vec2i.hpp"
#include "maskType.hpp"

namespace HokusBlokus::Blokus {
    class PieceBitmask {
    private:
        std::bitset<484> bitmask;
        Vec2i maskDimensions;
        MaskType maskType;

    public:
        PieceBitmask();
        
        PieceBitmask(std::bitset<484> bitmask, MaskType maskType);

        bool operator==(const PieceBitmask& other) const;

        const std::bitset<484>& GetBitmask() const;

        const Vec2i& GetMaskDimensions() const;
        
        MaskType GetMaskType() const;

    private:
        Vec2i ComputeMaskDimensions(const std::bitset<484>& bitmask) const;
    };
}