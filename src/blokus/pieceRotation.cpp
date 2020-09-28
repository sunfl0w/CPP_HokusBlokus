#include "pieceRotation.hpp"

namespace HokusBlokus::Blokus {
    PieceRotation StringToPieceRotation(std::string pieceRotationString) {
        if (pieceRotationString == "NONE") {
            return PieceRotation::NONE;
        } else if (pieceRotationString == "RIGHT") {
            return PieceRotation::RIGHT;
        } else if (pieceRotationString == "MIRROR") {
            return PieceRotation::MIRROR;
        } else if (pieceRotationString == "LEFT") {
            return PieceRotation::LEFT;
        } else {
            std::cout << "Unable to convert: " << pieceRotationString << " to a valid PieceRotation\n";
            exit(1);
        }
    }

    std::string PieceRotationToString(PieceRotation pieceRotation) {
        if(pieceRotation == PieceRotation::NONE) {
            return "NONE";
        } else if(pieceRotation == PieceRotation::RIGHT) {
            return "RIGHT";
        } else if(pieceRotation == PieceRotation::MIRROR) {
            return "MIRROR";
        } else {
            return "LEFT";
        }
    }
}  // namespace HokusBlokus::Blokus