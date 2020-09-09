#include "move.hpp"

namespace HokusBlokus::Blokus {
    Move::Move(const Vec2ui& destination, PieceShape pieceShape, Color color) : destination(destination), pieceShape(pieceShape), color(color) {
    }

    const Vec2ui& Move::GetDestination() {
        return destination;
    }

    const PieceShape Move::GetPieceShape() {
        return pieceShape;
    }

    const Color Move::GetColor() {
        return color;
    }
}