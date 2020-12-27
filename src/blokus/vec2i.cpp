#include "vec2i.hpp"

namespace HokusBlokus::Blokus {
    Vec2i::Vec2i() {}
    
    Vec2i::Vec2i(int x, int y) :x(x), y(y) {
    }

    bool Vec2i::operator==(const Vec2i& other) const {
        return x == other.x && y == other.y;
    }
}