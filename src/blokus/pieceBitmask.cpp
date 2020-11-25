#include "pieceBitmask.hpp"

namespace HokusBlokus::Blokus {
    PieceBitmask::PieceBitmask() : maskDimensions(0, 0) {}

    PieceBitmask::PieceBitmask(std::bitset<484> bitmask, MaskType maskType) : maskDimensions(0, 0) {
        this->bitmask = bitmask;
        this->maskType = maskType;
        this->maskDimensions = ComputeMaskDimensions(bitmask);
    }

    bool PieceBitmask::operator==(const PieceBitmask& other) const {
        return bitmask == other.bitmask && maskType == other.maskType && maskDimensions == other.maskDimensions;
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

    std::string PieceBitmask::Draw() const {
        std::stringstream stream;

        stream << "----------\n";
        for (int y = 0; y < 22; y++) {
            std::string line;
            for (int x = 0; x < 22; x++) {
                if (bitmask[x + 22 * y]) {
                    line += "1";
                } else {
                    line += "0";
                }
            }
            stream << line << "\n";
        }
        stream << "----------\n";
        return stream.str();
    }

    // PRIVATE

    Vec2i PieceBitmask::ComputeMaskDimensions(const std::bitset<484>& bitmask) const {
        int minX = 21;
        int maxX = 0;
        int minY = 21;
        int maxY = 0;

        for (int y = 0; y < 22; y++) {
            for (int x = 0; x < 22; x++) {
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