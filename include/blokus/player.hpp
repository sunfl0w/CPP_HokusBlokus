#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include "color.hpp"
#include "pieceShape.hpp"

namespace HokusBlokus::Blokus {
    class Player {
        Color color0;
        Color color1;

        std::vector<int> undeployedPieceShapeIDs0;
        std::vector<int> undeployedPieceShapeIDs1;

    public:
        Player(Color color0, Color color1);

        void PopulateUndeployedPieces();

        const std::vector<int>& GetUndeployedPieceShapeIDs(Color color) const;

        void AddUndeployedPieceShape(Color color, PieceShape pieceShape);

        void RemoveUndeployedPieceShape(Color color, PieceShape pieceShape);
    };
}  // namespace HokusBlokus::Blokus