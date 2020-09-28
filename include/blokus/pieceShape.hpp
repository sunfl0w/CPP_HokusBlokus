#pragma once

#include <string>
#include <iostream>

namespace HokusBlokus::Blokus {
    enum class PieceShape {
        MONOMINO = 0,
        DOMINO = 1,
        TRIO_L = 2,
        TRIO_I = 3,
        TETRO_I = 4,
        TETRO_L = 5,
        TETRO_O = 6,
        TETRO_T = 7,
        TETRO_Z = 8,
        PENTO_I = 9,
        PENTO_U = 10,
        PENTO_L = 11,
        PENTO_V = 12,
        PENTO_P = 13,
        PENTO_W = 14,
        PENTO_R = 15,
        PENTO_X = 16,
        PENTO_Z = 17,
        PENTO_Y = 18,
        PENTO_T = 19,
        PENTO_S = 20
    };

    int PieceShapeToInt(PieceShape pieceShape);

    PieceShape IntToPieceShape(int value);

    PieceShape StringToPieceShape(std::string pieceShapeString);
}