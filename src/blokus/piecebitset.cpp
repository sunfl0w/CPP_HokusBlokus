#include "piecebitset.hpp"

namespace HokusBlokus::Blokus {
    PieceBitset::PieceBitset(std::bitset<484> bitset, MaskType maskType) : maskDimensions(0, 0) {
        this->bitset = bitset;
        this->maskType = maskType;
        this->maskDimensions = ComputeMaskDimensions(this->bitset);
    }

    const std::bitset<484>& PieceBitset::GetBitset() const {
        return bitset;
    }

    const Vec2ui& PieceBitset::GetMaskDimensions() const {
        return maskDimensions;
    }

    MaskType PieceBitset::GetMaskType() const {
        return maskType;
    }

    bool PieceBitset::operator==(const PieceBitset& other) {
        return bitset == other.bitset;
    }

    //PRIVATE

    Vec2ui PieceBitset::ComputeMaskDimensions(const std::bitset<484>& bitset) const {
        Vec2ui dimensions = Vec2ui(0, 0);

        unsigned int minX = 21;
        unsigned int maxX = 0;
        unsigned int minY = 21;
        unsigned int maxY = 0;

        for(unsigned int y = 0; y < 22; y++) {
            for(unsigned int x = 0; x < 22; x++) {
                if(bitset[x + y * 22]) { 
                    minX = std::min(minX, x);
                    maxX = std::max(maxX, x + 1);
                    minY = std::min(minY, y);
                    maxY = std::max(maxY, y + 1);
                }
            }
        }
        dimensions.x = maxX - minX;
        dimensions.y = maxY - minY;
        return dimensions;
    }
}  // namespace HokusBlokus::Blokus