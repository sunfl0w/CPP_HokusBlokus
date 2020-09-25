#include "move.hpp"

namespace HokusBlokus::Blokus {
    Move::Move(Vec2i destination, PieceShape pieceShape, unsigned int complementNumber, Color color, MoveType moveType) : destination(destination), pieceShape(pieceShape), complementNumber(complementNumber), color(color), moveType(moveType) {
    }

    bool Move::operator==(const Move& other) {
        return destination == other.destination && pieceShape == other.pieceShape && complementNumber == other.complementNumber && color == other.color && moveType == other.moveType;
    }

    bool Move::operator!=(const Move& other) {
        return !(*this == other);
    }


    const Vec2i& Move::GetDestination() const {
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