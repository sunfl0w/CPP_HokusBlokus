#include "pieceShape.hpp"

namespace HokusBlokus::Blokus {
    int PieceShapeToInt(PieceShape pieceShape) {
        return static_cast<int>(pieceShape);
    }

    PieceShape IntToPieceShape(int value) {
        return static_cast<PieceShape>(value);
    }
}