#pragma once

#include <vector>
#include <array>
#include <bitset>
#include <algorithm>

#include "pieceBitmask.hpp"
#include "pieceBitmaskComplement.hpp"

namespace HokusBlokus::Blokus {
    class Piece {
    private:
        std::vector<PieceBitmaskComplement> pieceBitmaskComplements;

    public:
        Piece(std::vector<PieceBitmaskComplement> pieceBitmaskComplements);

        const std::vector<PieceBitmaskComplement>& GetPieceBitmaskComplements() const;

    private:
        std::vector<PieceBitmaskComplement> FilterDuplicateBitmaskComplements(const std::vector<PieceBitmaskComplement>& pieceBitmaskComplements) const;
    };
}