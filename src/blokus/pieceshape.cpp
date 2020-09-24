#include "pieceshape.hpp"

namespace HokusBlokus::Blokus {
    unsigned int PieceShapeToUInt(PieceShape pieceShape) {
        return static_cast<unsigned int>(pieceShape);
    }

    PieceShape UIntToPieceShape(unsigned int value) {
        return static_cast<PieceShape>(value);
    }
}