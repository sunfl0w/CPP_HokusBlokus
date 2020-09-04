#include "move.hpp"

namespace Blokus {
    Move::Move(const Position& destination, Piece piece, Color color) : destination(destination), piece(piece), color(color) {
    }

    const Position& Move::GetDestination() {
        return destination;
    }

    const Piece Move::GetPiece() {
        return piece;
    }

    const Color Move::GetColor() {
        return color;
    }
}