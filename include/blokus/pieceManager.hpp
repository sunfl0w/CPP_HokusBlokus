#pragma once

#include <bitset>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "pieceShape.hpp"
#include "pieceBitmask.hpp"
#include "pieceBitmaskComplement.hpp"
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

        static std::array<std::array<PieceBitmaskComplement, 8>, 21> LoadBitmasks();

        static std::array<std::bitset<484>, 21> PBMPieceDataToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize, const Vec2i& offset);
    };
}  // namespace HokusBlokus::Blokus