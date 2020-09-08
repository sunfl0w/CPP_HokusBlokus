#pragma once

#include "color.hpp"
#include "piecetype.hpp"
#include "vec2ui.hpp"

namespace HokusBlokus::Blokus {
    class Move {
    private:
        Vec2ui destination;
        PieceType pieceType;
        Color color;

    public:
        Move(const Vec2ui& destination, PieceType pieceType, Color color);

        const Vec2ui& GetDestination();
        const PieceType GetPieceType();
        const Color GetColor();
    };
}  // namespace Blokus