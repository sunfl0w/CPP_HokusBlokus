#pragma once

#include <bitset>
#include <vector>
#include <iostream>
#include <fstream>

#include "pieceshape.hpp"
#include "vec2ui.hpp"
#include "pbmimage.hpp"
#include "pbmloader.hpp"

namespace HokusBlokus::Blokus {
    class BitsetManager {
        static std::vector<std::bitset<484>> pieceShapeBitsets;
        static std::vector<std::bitset<484>> pieceEdgeBitsets;
        static std::vector<std::bitset<484>> pieceCornerBitsets;

        static std::vector<Vec2ui> pieceShapeDimensions;
        static std::vector<Vec2ui> pieceEdgeCornerDimensions;

    public:
        static void LoadBitsets();

        static void LoadPieceDimensions();

        static std::bitset<484>& GetShapeBitsetOfPiece(PieceShape pieceShape);

        static std::bitset<484>& GetEdgeBitsetOfPiece(PieceShape pieceShape);

        static std::bitset<484>& GetCornerBitsetOfPiece(PieceShape pieceShape);

        static Vec2ui& GetDimensionsOfPiece(PieceShape pieceShape);

        static Vec2ui& GetEdgeDimensionsOfPiece(PieceShape pieceShape);

    private:
        BitsetManager();

        static std::vector<std::bitset<484>> PBMPiecesToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize);

        static std::vector<Vec2ui> LoadDimensionListingFromFile(std::string path);
    };
}  // namespace HokusBlokus::Blokus