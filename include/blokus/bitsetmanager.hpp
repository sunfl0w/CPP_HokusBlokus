#pragma once

#include <bitset>
#include <vector>

#include "piecetype.hpp"
#include "vec2ui.hpp"

namespace HokusBlokus::Blokus {
    class BitsetManager {
        std::vector<std::bitset<400>> pieceBitsets = std::vector<std::bitset<400>>();

    public:
        static std::bitset<400>& GetBitsetOfPiece(PieceType pieceType);
        static Vec2ui& GetDimensionsOfPiece(PieceType pieceType);
        static Vec2ui& GetEdgeDimensionsOfPiece(PieceType pieceType);

    private:
        BitsetManager();
    };
}  // namespace HokusBlokus::Blokus