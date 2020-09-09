#pragma once

namespace HokusBlokus::Blokus {
    enum class Color {
        BLUE = 0,
        YELLOW = 1,
        RED = 2,
        GREEN = 3,
    };

    static unsigned int ColorToUInt(Color color) {
        return static_cast<unsigned int>(color);
    }

    static Color UIntToColor(unsigned int value) {
        return static_cast<Color>(value);
    }
}