#pragma once

#include "vec2i.hpp"

namespace HokusBlokus::Blokus::Optimization {
    class BoundingRect {
        Vec2i minBounds;
        Vec2i maxBounds;

    public:
        BoundingRect();

        BoundingRect(const Vec2i& minBounds, const Vec2i& maxBounds);

        const Vec2i& GetMinBounds();

        void SetMinBounds(const Vec2i& minBounds);

        const Vec2i& GetMaxBounds();

        void SetMaxBounds(const Vec2i& maxBounds);
    };
}