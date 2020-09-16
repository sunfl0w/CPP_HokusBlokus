#pragma once

#include <vector>
#include <bitset>
#include <algorithm>

#include "vec2ui.hpp"
#include "piecebitset.hpp"

namespace HokusBlokus::Blokus {
    class Piece {
    private:
        std::vector<PieceBitset> pieceShapeBitsets;
        std::vector<PieceBitset> pieceCornerBitsets;
        std::vector<PieceBitset> pieceEdgeBitsets;

    public:
        Piece(std::vector<PieceBitset> pieceBitsets);

        const std::vector<PieceBitset>& GetPieceShapeBitsets() const;

        const std::vector<PieceBitset>& GetPieceCornerBitsets() const;

        const std::vector<PieceBitset>& GetPieceEdgeBitsets() const;

    private:
        std::vector<PieceBitset> FilterDuplicateBitsets(const std::vector<PieceBitset>& pieceBitsets) const;
    };
}