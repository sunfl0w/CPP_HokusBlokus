#pragma once

#include <bitset>

#include "vec2ui.hpp"
#include "masktype.hpp"

namespace HokusBlokus::Blokus {
    class PieceBitset {
    private:
        std::bitset<484> bitset;
        Vec2ui maskDimensions;
        MaskType maskType;

    public:
        PieceBitset(std::bitset<484> bitset, MaskType maskType);

        const std::bitset<484>& GetBitset() const;

        const Vec2ui& GetMaskDimensions() const;
        
        MaskType GetMaskType() const;

        bool operator==(const PieceBitset& other);

    private:
        Vec2ui ComputeMaskDimensions(const std::bitset<484>& bitset) const;
    };
}