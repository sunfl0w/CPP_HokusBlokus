#include "boundingRectOptimizer.hpp"

namespace HokusBlokus::Blokus::Optimization {
    BoundingRectOptimizer::BoundingRectOptimizer() {
        boundingRects = std::array<BoundingRect, 4>();

        for(unsigned int i = 0; i < 4; i++) {
            boundingRects[i].SetMinBounds(Vec2i(0, 0));
            boundingRects[i].SetMaxBounds(Vec2i(20, 20));
        }
    }

    const BoundingRect& BoundingRectOptimizer::GetBoundingRect(Color color) {
        return boundingRects[ColorToInt(color)];
    }

    void BoundingRectOptimizer::OptimizeBoundingRectOfColor(Color color, Board& board) {
        Vec2i minBounds = Vec2i(boundingRects[ColorToInt(color)].GetMinBounds());
        Vec2i maxBounds = Vec2i(boundingRects[ColorToInt(color)].GetMaxBounds());

        unsigned int minXT = 20;
        unsigned int minYT = 20;
        unsigned int maxXT = 1;
        unsigned int maxYT = 1;

        unsigned int searchMinX = std::max(1, minBounds.x - 5);
        unsigned int searchMinY = std::max(1, minBounds.y - 5);
        unsigned int searchMaxX = std::min(21, maxBounds.x + 5);
        unsigned int searchMaxY = std::min(21, maxBounds.y + 5);


        for(unsigned int x = searchMinX; x < searchMaxX; x++) {
            for(unsigned int y = searchMinY; y < searchMaxY; y++) {
                if(board.GetBitmask(color)[x + y * 22]) {
                    minXT = std::min(minXT, x);
                    minYT = std::min(minYT, y);
                    maxXT = std::max(maxXT, x);
                    maxYT = std::max(maxYT, y);
                }
            }
        }

        boundingRects[ColorToInt(color)].SetMinBounds(Vec2i(minXT, minYT));
        boundingRects[ColorToInt(color)].SetMaxBounds(Vec2i(maxXT, maxYT));

        /*unsigned int minX = 20;
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
        boundingRects[ColorToInt(color)].SetMaxBounds(Vec2i(maxX, maxY));*/
    }

    void BoundingRectOptimizer::OptimizeBoundingRectOfColorRevertedMove(Color color, Board& board) {
        Vec2i minBounds = Vec2i(boundingRects[ColorToInt(color)].GetMinBounds());
        Vec2i maxBounds = Vec2i(boundingRects[ColorToInt(color)].GetMaxBounds());

        unsigned int minXT = 20;
        unsigned int minYT = 20;
        unsigned int maxXT = 1;
        unsigned int maxYT = 1;

        unsigned int searchMinX = std::max(1, minBounds.x - 1);
        unsigned int searchMinY = std::max(1, minBounds.y - 1);
        unsigned int searchMaxX = std::min(21, maxBounds.x + 1);
        unsigned int searchMaxY = std::min(21, maxBounds.y + 1);


        for(unsigned int x = searchMinX; x < searchMaxX; x++) {
            for(unsigned int y = searchMinY; y < searchMaxY; y++) {
                if(board.GetBitmask(color)[x + y * 22]) {
                    minXT = std::min(minXT, x);
                    minYT = std::min(minYT, y);
                    maxXT = std::max(maxXT, x);
                    maxYT = std::max(maxYT, y);
                }
            }
        }

        boundingRects[ColorToInt(color)].SetMinBounds(Vec2i(minXT, minYT));
        boundingRects[ColorToInt(color)].SetMaxBounds(Vec2i(maxXT, maxYT));
    }
}