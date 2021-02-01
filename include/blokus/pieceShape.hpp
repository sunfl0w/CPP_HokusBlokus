#pragma once

#include <string>
#include <iostream>

#include "logger.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief Represents a PieceShape of a Blokus Piece
     * 
     */
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

    /**
     * @brief Converts a PieceShape to an int
     * 
     * @param pieceShape The PieceShape to convert
     * @return int 
     */
    int PieceShapeToInt(PieceShape pieceShape);

    /**
     * @brief Converts a PieceShape to a String
     * 
     * @param pieceShape The PieceShape to convert
     * @return std::string 
     */
    std::string PieceShapeToString(PieceShape pieceShape);

    /**
     * @brief Converts an int to a PieceShape
     * 
     * @param value The int to convert
     * @return PieceShape 
     */
    PieceShape IntToPieceShape(int value);

    /**
     * @brief Converts a String to a PieceShape
     * 
     * @param pieceShapeString The String to convert
     * @return PieceShape 
     */
    PieceShape StringToPieceShape(std::string pieceShapeString);
}