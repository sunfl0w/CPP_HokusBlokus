#include "pieceBitmask.hpp"

namespace HokusBlokus::Blokus {
    PieceBitmask::PieceBitmask() : maskDimensions(0, 0) {}

    PieceBitmask::PieceBitmask(std::bitset<484> bitmask, MaskType maskType) : maskDimensions(0, 0) {
        this->bitmask = bitmask;
        this->maskType = maskType;
        this->maskDimensions = ComputeMaskDimensions(this->bitmask);
    }

    const std::bitset<484>& PieceBitmask::GetBitmask() const {
        return bitmask;
    }

    const Vec2i& PieceBitmask::GetMaskDimensions() const {
        return maskDimensions;
    }

    MaskType PieceBitmask::GetMaskType() const {
        return maskType;
    }

    bool PieceBitmask::operator==(const PieceBitmask& other) {
        return bitmask == other.bitmask;
    }

    // PRIVATE

    Vec2i PieceBitmask::ComputeMaskDimensions(const std::bitset<484>& bitmask) const {
        unsigned int minX = 21;
        unsigned int maxX = 0;
        unsigned int minY = 21;
        unsigned int maxY = 0;

        for (unsigned int y = 0; y < 22; y++) {
            for (unsigned int x = 0; x < 22; x++) {
                if (bitmask[x + y * 22]) {
                    minX = std::min(minX, x);
                    maxX = std::max(maxX, x + 1);
                    minY = std::min(minY, y);
                    maxY = std::max(maxY, y + 1);
                }
            }
        }

        return Vec2i(maxX - minX, maxY - minY);
    }
}  // namespace HokusBlokus::Blokus