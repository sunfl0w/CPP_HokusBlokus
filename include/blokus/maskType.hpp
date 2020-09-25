#pragma once

namespace HokusBlokus::Blokus {
    enum class MaskType {
        Shape,
        Corner,
        Edge,
    };

    int MaskTypeToInt(MaskType maskType);

    MaskType IntToMaskType(int value);
}