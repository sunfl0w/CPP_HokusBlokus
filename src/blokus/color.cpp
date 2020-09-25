#include "color.hpp"

namespace HokusBlokus::Blokus {
    int ColorToInt(Color color) {
        return static_cast<int>(color);
    }

    Color IntToColor(int value) {
        return static_cast<Color>(value);
    }
}