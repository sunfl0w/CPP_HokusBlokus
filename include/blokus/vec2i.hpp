#pragma once

namespace HokusBlokus::Blokus {
    class Vec2i {
    public:
        int x, y;

        Vec2i(int x, int y);

        bool operator==(const Vec2i& other);
    };
}  // namespace Blokus