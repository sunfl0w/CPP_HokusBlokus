#include "color.hpp"

namespace HokusBlokus::Blokus {
    unsigned int ColorToUInt(Color color) {
        return static_cast<unsigned int>(color);
    }

    Color UIntToColor(unsigned int value) {
        return static_cast<Color>(value);
    }
}