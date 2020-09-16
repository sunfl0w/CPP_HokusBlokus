#pragma once

#include <vector>
#include <bitset>
#include <algorithm>

#include "vec2ui.hpp"
#include "piecebitmask.hpp"

namespace HokusBlokus::Blokus {
    class Piece {
    private:
        std::vector<PieceBitmask> pieceShapeBitmasks;
        std::vector<PieceBitmask> pieceCornerBitmasks;
        std::vector<PieceBitmask> pieceEdgeBitmasks;

    public:
        Piece(std::vector<PieceBitmask> pieceBitmasks);

        const std::vector<PieceBitmask>& GetPieceShapeBitmasks() const;

        const std::vector<PieceBitmask>& GetPieceCornerBitmasks() const;

        const std::vector<PieceBitmask>& GetPieceEdgeBitmasks() const;

    private:
        std::vector<PieceBitmask> FilterDuplicateBitmasks(const std::vector<PieceBitmask>& pieceBitmask) const;
    };
}