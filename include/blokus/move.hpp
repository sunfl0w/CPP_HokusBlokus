#pragma once

#include "color.hpp"
#include "piece.hpp"
#include "position.hpp"

namespace HokusBlokus::Blokus {
    class Move {
    private:
        Position destination;
        Piece piece;
        Color color;

    public:
        Move(const Position& destination, Piece piece, Color color);

        const Position& GetDestination();
        const Piece GetPiece();
        const Color GetColor();
    };
}  // namespace Blokus