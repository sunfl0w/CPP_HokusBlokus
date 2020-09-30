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
        bool flipped;

    public:
        PieceBitmaskComplement();

        PieceBitmaskComplement(std::array<PieceBitmask, 3> bitmasks, PieceRotation rotation, bool flipped);

        bool operator==(const PieceBitmaskComplement& other);

        const PieceBitmask& GetBitmask(MaskType maskType) const;

        PieceRotation GetRotation() const;

        bool IsFlipped() const;
    };
}  // namespace HokusBlokus::Blokus