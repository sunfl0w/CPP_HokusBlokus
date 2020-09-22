#include "move.hpp"

namespace HokusBlokus::Blokus {
    Move::Move(Vec2ui destination, PieceShape pieceShape, unsigned int complementNumber, Color color, MoveType moveType) : destination(destination), pieceShape(pieceShape), complementNumber(complementNumber), color(color), moveType(moveType) {
    }

    const Vec2ui& Move::GetDestination() const {
        return destination;
    }

    PieceShape Move::GetPieceShape() const {
        return pieceShape;
    }

    unsigned int Move::GetComplementNumber() const {
        return complementNumber;
    }

    Color Move::GetColor() const {
        return color;
    }

    MoveType Move::GetMoveType() const {
        return moveType;
    }
}