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
        std::vector<std::bitset<484>> pieceShapeBitsets;
        std::vector<std::bitset<484>> pieceEdgeBitsets;
        std::vector<std::bitset<484>> pieceCornerBitsets;

        std::vector<Vec2ui> pieceShapeDimensions;
        std::vector<Vec2ui> pieceEdgeCornerDimensions;

    public:
        BitsetManager();

        void LoadBitsets();

        void LoadPieceDimensions();

        std::bitset<484>& GetShapeBitsetOfPiece(PieceShape pieceShape);

        std::bitset<484>& GetEdgeBitsetOfPiece(PieceShape pieceShape);

        std::bitset<484>& GetCornerBitsetOfPiece(PieceShape pieceShape);

        Vec2ui& GetDimensionsOfPiece(PieceShape pieceShape);

        Vec2ui& GetEdgeDimensionsOfPiece(PieceShape pieceShape);

    private:
        std::vector<std::bitset<484>> PBMPiecesToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize);

        std::vector<Vec2ui> LoadDimensionListingFromFile(std::string path);
    };
}  // namespace HokusBlokus::Blokus