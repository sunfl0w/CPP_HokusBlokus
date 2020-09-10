#pragma once

#include "color.hpp"
#include "pieceshape.hpp"
#include "vec2ui.hpp"

namespace HokusBlokus::Blokus {
    class Move {
    private:
        Vec2ui destination;
        PieceShape pieceShape;
        Color color;

    public:
        Move(const Vec2ui& destination, PieceShape pieceShape, Color color);

        const Vec2ui& GetDestination();
        const PieceShape GetPieceShape();
        const Color GetColor();
    };
}  // namespace Blokus