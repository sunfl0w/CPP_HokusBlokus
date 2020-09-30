#include "pieceBitmaskComplement.hpp"

namespace HokusBlokus::Blokus {
    PieceBitmaskComplement::PieceBitmaskComplement() {}

    PieceBitmaskComplement::PieceBitmaskComplement(std::array<PieceBitmask, 3> bitmasks, PieceRotation rotation, bool flipped) {
        this->bitmasks = bitmasks;
        this->rotation = rotation;
        this->flipped = flipped;
    }

    bool PieceBitmaskComplement::operator==(const PieceBitmaskComplement& other) {
        return bitmasks == other.bitmasks;
    }

    const PieceBitmask& PieceBitmaskComplement::GetBitmask(MaskType maskType) const {
        return bitmasks[MaskTypeToInt(maskType)];
    }

    PieceRotation PieceBitmaskComplement::GetRotation() const {
        return rotation;
    }

    bool PieceBitmaskComplement::IsFlipped() const {
        return flipped;
    }
}  // namespace HokusBlokus::Blokus