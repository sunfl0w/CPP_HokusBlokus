#pragma once

#include <vector>
#include <array>
#include <bitset>
#include <algorithm>

#include "pieceBitmask.hpp"

namespace HokusBlokus::Blokus {
    class Piece {
    private:
        std::vector<std::array<PieceBitmask, 3>> pieceBitmaskComplements;

    public:
        Piece(std::vector<PieceBitmask> pieceBitmasks);

        const std::vector<std::array<PieceBitmask, 3>>& GetPieceBitmaskComplements() const;

    private:
        std::vector<PieceBitmask> FilterDuplicateBitmasks(const std::vector<PieceBitmask>& pieceBitmask) const;
    };
}