#pragma once

#include "color.hpp"
#include "pieceShape.hpp"
#include "vec2i.hpp"
#include "moveType.hpp"

namespace HokusBlokus::Blokus {
    class Move {
    private:
        Vec2i destination;
        PieceShape pieceShape;
        unsigned int complementNumber;
        Color color;
        MoveType moveType;

    public:
        Move(Vec2i destination, PieceShape pieceShape, unsigned int complementNumber, Color color, MoveType moveType);

        bool operator==(const Move& other);

        bool operator!=(const Move& other);

        const Vec2i& GetDestination() const;

        PieceShape GetPieceShape() const;

        unsigned int GetComplementNumber() const;

        Color GetColor() const;
        
        MoveType GetMoveType() const;
    };
}  // namespace Blokus