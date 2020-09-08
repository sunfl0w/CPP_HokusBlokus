#include "move.hpp"

namespace HokusBlokus::Blokus {
    Move::Move(const Vec2ui& destination, PieceType pieceType, Color color) : destination(destination), pieceType(pieceType), color(color) {
    }

    const Vec2ui& Move::GetDestination() {
        return destination;
    }

    const PieceType Move::GetPieceType() {
        return pieceType;
    }

    const Color Move::GetColor() {
        return color;
    }
}