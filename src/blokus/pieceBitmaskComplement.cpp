#include "pieceBitmaskComplement.hpp"

namespace HokusBlokus::Blokus {
    PieceBitmaskComplement::PieceBitmaskComplement(std::array<PieceBitmask, 3> bitmasks, PieceRotation rotation, bool mirrored) {
        this->bitmasks = bitmasks;
        this->rotation = rotation;
        this->mirrored = mirrored;
    }

    PieceBitmask& PieceBitmaskComplement::GetBitmask(MaskType maskType) {
        return bitmasks[MaskTypeToInt(maskType)];
    }

    PieceRotation PieceBitmaskComplement::GetRotation() {
        return rotation;
    }

    bool PieceBitmaskComplement::IsMirrored() {
        return mirrored;
    }
}  // namespace HokusBlokus::Blokus