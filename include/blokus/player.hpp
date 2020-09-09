#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include "color.hpp"

namespace HokusBlokus::Blokus {
    class Player {
        Color color0;
        Color color1;

        std::vector<unsigned int> undeployedPieceShapeIDs0;
        std::vector<unsigned int> undeployedPieceShapeIDs1;

    public:
        Player(Color color0, Color color1);

        void PopulateUndeployedPieces();

        const std::vector<unsigned int>& GetUndeployedPieceShapeIDs(Color color) const;

        void RemovePieceShapeID0(Color color,unsigned int id);
    };
}  // namespace HokusBlokus::Blokus