#pragma once

namespace HokusBlokus::Blokus {
    enum class MaskType {
        Shape,
        Corner,
        Edge,
    };

    unsigned int MaskTypeToUInt(MaskType maskType);

    MaskType UIntToMaskType(unsigned int value);
}