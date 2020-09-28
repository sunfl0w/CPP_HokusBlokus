#pragma once

#include <array>
#include <vector>

#include "maskType.hpp"
#include "pieceBitmask.hpp"
#include "pieceRotation.hpp"

namespace HokusBlokus::Blokus {
    class PieceBitmaskComplement {
        std::array<PieceBitmask, 3> bitmasks;
        PieceRotation rotation;
        bool mirrored;

    public:
        PieceBitmaskComplement(std::array<PieceBitmask, 3> bitmasks, PieceRotation rotation, bool mirrored);

        PieceBitmask& GetBitmask(MaskType maskType);

        PieceRotation GetRotation();

        bool IsMirrored();
    };
}  // namespace HokusBlokus::Blokus