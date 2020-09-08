#pragma once

#include <bitset>
#include <vector>

#include "piecetype.hpp"
#include "vec2ui.hpp"
#include "pbmimage.hpp"

namespace HokusBlokus::Blokus {
    class BitsetManager {
        static std::vector<std::bitset<484>> pieceBitsets;
        static std::vector<std::bitset<484>> pieceEdgeBitsets;
        static std::vector<std::bitset<484>> pieceCornerBitsets;

    public:
        static void InitBitsetManager(PBM::PBMImage pieceBitmap, PBM::PBMImage pieceEdgeBitmap, PBM::PBMImage pieceCornerBitmap);

        static std::bitset<484>& GetBitsetOfPiece(PieceType pieceType);

        static std::bitset<484>& GetEdgeBitsetOfPiece(PieceType pieceType);

        static std::bitset<484>& GetCornerBitsetOfPiece(PieceType pieceType);

        static Vec2ui& GetDimensionsOfPiece(PieceType pieceType);

        static Vec2ui& GetEdgeDimensionsOfPiece(PieceType pieceType);

    private:
        BitsetManager();
    };
}  // namespace HokusBlokus::Blokus