#include "color.hpp"

namespace HokusBlokus::Blokus {
    int ColorToInt(Color color) {
        return static_cast<int>(color);
    }

    std::string ColorToString(Color color) {
        if(color == Color::BLUE) {
            return "BLUE";
        } else if(color == Color::YELLOW) {
            return "YELLOW";
        } else if(color == Color::RED) {
            return "RED";
        } else {
            return "GREEN";
        }
    }

    Color IntToColor(int value) {
        return static_cast<Color>(value);
    }
}