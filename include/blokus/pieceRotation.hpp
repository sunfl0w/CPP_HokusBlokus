#pragma once

#include <string>
#include <iostream>

namespace HokusBlokus::Blokus {
    enum class PieceRotation {
        NONE,
        RIGHT,
        MIRROR,
        LEFT,
    };

    PieceRotation StringToPieceRotation(std::string pieceRotationString);

    std::string PieceRotationToString(PieceRotation pieceRotation);
}