#pragma once

namespace HokusBlokus::Blokus {
    enum class Color {
        BLUE = 0,
        YELLOW = 1,
        RED = 2,
        GREEN = 3,
    };

    int ColorToInt(Color color);

    Color IntToColor(int value);
}