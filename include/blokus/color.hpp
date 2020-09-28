#pragma once

#include <string>

namespace HokusBlokus::Blokus {
    enum class Color {
        BLUE = 0,
        YELLOW = 1,
        RED = 2,
        GREEN = 3,
    };

    int ColorToInt(Color color);

    std::string ColorToString(Color color);

    Color IntToColor(int value);
}