#include "maskType.hpp"

namespace HokusBlokus::Blokus {
    int MaskTypeToInt(MaskType maskType) {
        return static_cast<int>(maskType);
    }

    MaskType IntToMaskType(int value) {
        return static_cast<MaskType>(value);
    }
}