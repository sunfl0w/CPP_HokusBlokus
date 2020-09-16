#pragma once

#include <vector>
#include <bitset>
#include <algorithm>

#include "vec2ui.hpp"

namespace HokusBlokus::Blokus {
    class Piece {
    private:
        std::vector<std::bitset<484>> pieceShapeBitsets;
        std::vector<std::bitset<484>> pieceCornerBitsets;
        std::vector<std::bitset<484>> pieceEdgeBitsets;
        Vec2ui pieceShapeDimensions;
        Vec2ui pieceEdgeCornerDimensions;

    public:
        Piece(std::vector<std::bitset<484>> pieceShapeBitsets, std::vector<std::bitset<484>> pieceCornerBitsets, std::vector<std::bitset<484>> pieceEdgeBitsets, Vec2ui pieceShapeDimensions);

        const std::vector<std::bitset<484>>& GetPieceShapeBitsets() const;

        const std::vector<std::bitset<484>>& GetPieceCornerBitsets() const;

        const std::vector<std::bitset<484>>& GetPieceEdgeBitsets() const;

        const Vec2ui& GetPieceShapeDimensions() const;

        const Vec2ui& GetPieceEdgeCornerDimensions() const;

    private:
        std::vector<std::bitset<484>> FilterDuplicateBitsets(const std::vector<std::bitset<484>>& pieceBitsets) const;
    };
}