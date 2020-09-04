#pragma once

#include "color.hpp"
#include "piece.hpp"
#include "position.hpp"

namespace Blokus {
    class Move {
    private:
        Position position;
        Piece piece;
        Color color;

    public:
        Move(const Position& position, Piece piece, Color color);
    };
}  // namespace Blokus