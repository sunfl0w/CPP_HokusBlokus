#pragma once

namespace HokusBlokus::Blokus {
    enum class Color {
        BLUE = 0,
        YELLOW = 1,
        RED = 2,
        GREEN = 3,
    };

    unsigned int ColorToUInt(Color color);

    Color UIntToColor(unsigned int value);
}