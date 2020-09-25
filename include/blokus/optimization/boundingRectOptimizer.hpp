#pragma once

#include <array>

#include "boundingRect.hpp"
#include "color.hpp"
#include "board.hpp"

namespace HokusBlokus::Blokus::Optimization {
    class BoundingRectOptimizer {
        std::array<BoundingRect, 4> boundingRects;

    public:
        BoundingRectOptimizer();

        const BoundingRect& GetBoundingRect(Color color);

        void OptimizeBoundingRectOfColor(Color color, Board board);
    };
}  // namespace HokusBlokus::Blokus::Optimization