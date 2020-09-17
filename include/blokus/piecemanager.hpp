#pragma once

#include <bitset>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "pieceshape.hpp"
#include "piecebitmask.hpp"
#include "vec2ui.hpp"
#include "pbmimage.hpp"
#include "pbmloader.hpp"
#include "piece.hpp"

namespace HokusBlokus::Blokus {
    class PieceManager {
        static std::vector<Piece> pieces;

    public:
        static void Init();

        static Piece& GetPiece(PieceShape pieceShape);

    private:
        PieceManager();

        static std::array<std::vector<PieceBitmask>, 21> LoadBitmasks();

        static std::vector<Vec2ui> LoadPieceDimensions();

        static std::vector<std::bitset<484>> PBMPieceDataToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize, const Vec2ui& offset);

        static std::vector<Vec2ui> LoadPieceDataDimensionsFromFile(std::string path);
    };
}  // namespace HokusBlokus::Blokus