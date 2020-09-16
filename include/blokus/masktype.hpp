#pragma once

namespace HokusBlokus::Blokus {
    enum class MaskType {
        Shape,
        Corner,
        Edge,
    };

    static unsigned int MaskTypeToUInt(MaskType maskType) {
        return static_cast<unsigned int>(maskType);
    }

    static MaskType UIntToMaskType(unsigned int value) {
        return static_cast<MaskType>(value);
    }
}