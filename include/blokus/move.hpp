#pragma once

#include "color.hpp"
#include "pieceShape.hpp"
#include "vec2i.hpp"
#include "moveType.hpp"
#include "pieceRotation.hpp"

namespace HokusBlokus::Blokus {
    class Move {
    private:
        Vec2i destination;
        PieceShape pieceShape;
        Color color;
        MoveType moveType;
        PieceRotation pieceRotation;
        bool mirrored;
        int complementNumber;

    public:
        Move(Vec2i destination, PieceShape pieceShape, Color color, MoveType moveType, int complementNumber);

        bool operator==(const Move& other);

        bool operator!=(const Move& other);

        const Vec2i& GetDestination() const;

        PieceShape GetPieceShape() const;

        Color GetColor() const;
        
        MoveType GetMoveType() const;

        int GetComplementNumber() const;
    };
}  // namespace Blokus