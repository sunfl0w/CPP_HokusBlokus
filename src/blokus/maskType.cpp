#include "maskType.hpp"

namespace HokusBlokus::Blokus {
    int MaskTypeToUInt(MaskType maskType) {
        return static_cast<int>(maskType);
    }

    MaskType UIntToMaskType(int value) {
        return static_cast<MaskType>(value);
    }
}