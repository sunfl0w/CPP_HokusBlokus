#pragma once

#include "color.hpp"
#include "pieceshape.hpp"
#include "vec2ui.hpp"
#include "moveType.hpp"

namespace HokusBlokus::Blokus {
    class Move {
    private:
        Vec2ui destination;
        PieceShape pieceShape;
        Color color;
        MoveType moveType;

    public:
        Move(Vec2ui destination, PieceShape pieceShape, Color color, MoveType moveType);

        const Vec2ui& GetDestination();

        const PieceShape GetPieceShape();

        const Color GetColor();
        
        const MoveType GetMoveType();
    };
}  // namespace Blokus