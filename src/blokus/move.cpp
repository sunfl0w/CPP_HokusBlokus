#include "move.hpp"

namespace HokusBlokus::Blokus {
    Move::Move(Vec2ui destination, PieceShape pieceShape, Color color, MoveType moveType) : destination(destination), pieceShape(pieceShape), color(color), moveType(moveType) {
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

    const MoveType Move::GetMoveType() {
        return moveType;
    }
}