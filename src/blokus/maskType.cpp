#include "maskType.hpp"

namespace HokusBlokus::Blokus {
    unsigned int MaskTypeToUInt(MaskType maskType) {
        return static_cast<unsigned int>(maskType);
    }

    MaskType UIntToMaskType(unsigned int value) {
        return static_cast<MaskType>(value);
    }
}