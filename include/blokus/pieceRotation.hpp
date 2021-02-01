#pragma once

#include <string>
#include <iostream>

namespace HokusBlokus::Blokus {
    /**
     * @brief Represents a rotation of a Piece
     * 
     */
    enum class PieceRotation {
        NONE,
        RIGHT,
        MIRROR,
        LEFT,
    };

    /**
     * @brief Converts a String to a PieceRotation
     * 
     * @param pieceRotationString The String to convert
     * @return PieceRotation 
     */
    PieceRotation StringToPieceRotation(std::string pieceRotationString);

    /**
     * @brief Converts a PieceRotation to a String
     * 
     * @param pieceRotation The PieceRotation to convert
     * @return std::string 
     */
    std::string PieceRotationToString(PieceRotation pieceRotation);
}