#include "move.hpp"

namespace HokusBlokus::Blokus {
    Move::Move(Vec2i destination, PieceShape pieceShape, Color color, MoveType moveType, int complementNumber) : destination(destination) {
        this->pieceShape = pieceShape;
        this->color = color;
        this->moveType = moveType;
        this->complementNumber = complementNumber;
    }

    bool Move::operator==(const Move& other) {
        return destination == other.destination && pieceShape == other.pieceShape && color == other.color && moveType == other.moveType && pieceRotation == other.pieceRotation &&
               mirrored == other.mirrored && complementNumber == other.complementNumber;
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

    Color Move::GetColor() const {
        return color;
    }

    MoveType Move::GetMoveType() const {
        return moveType;
    }

    int Move::GetComplementNumber() const {
        return complementNumber;
    }
}  // namespace HokusBlokus::Blokus