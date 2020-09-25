#include "boundingRectOptimizer.hpp"

namespace HokusBlokus::Blokus::Optimization {
    BoundingRectOptimizer::BoundingRectOptimizer() {
        boundingRects = std::array<BoundingRect, 4>();

        for(unsigned int i = 0; i < 4; i++) {
            boundingRects[i].SetMaxBounds(Vec2i(20, 20));
        }
    }

    const BoundingRect& BoundingRectOptimizer::GetBoundingRect(Color color) {
        return boundingRects[ColorToInt(color)];
    }

    void BoundingRectOptimizer::OptimizeBoundingRectOfColor(Color color, Board board) {
        unsigned int minX = 20;
        unsigned int minY = 20;
        unsigned int maxX = 1;
        unsigned int maxY = 1;

        for(unsigned int x = 1; x < 21; x++) {
            for(unsigned int y = 1; y < 21; y++) {
                if(board.GetBitmask(color)[x + y * 22]) {
                    minX = std::min(minX, x);
                    minY = std::min(minY, y);
                    maxX = std::max(maxX, x);
                    maxY = std::max(maxY, y);
                }
            }
        }

        boundingRects[ColorToInt(color)].SetMinBounds(Vec2i(minX, minY));
        boundingRects[ColorToInt(color)].SetMaxBounds(Vec2i(maxX, maxY));
    }
}