#include "player.hpp"

namespace HokusBlokus::Blokus {
    Player::Player(Color color0, Color color1) : color0(color0), color1(color1) {
    }

    void Player::PopulateUndeployedPieces() {
        undeployedPieceShapeIDs0 = std::vector<int>();
        undeployedPieceShapeIDs1 = std::vector<int>();
        for (int i = 0; i < 21; i++) {
            undeployedPieceShapeIDs0.push_back(i);
            undeployedPieceShapeIDs1.push_back(i);
        }
    }

    const std::vector<int>& Player::GetUndeployedPieceShapeIDs(Color color) const {
        //TODO: Make this brancheless. Should be possible with edits to the class

        if (color == color0) {
            return undeployedPieceShapeIDs0;
        } else if (color == color1) {
            return undeployedPieceShapeIDs1;
        } else {
            std::cout << "Player does not play with the given color.\n";
            exit(1);
        }
    }

    void Player::AddUndeployedPieceShape(Color color, PieceShape pieceShape) {
        //TODO: Make this brancheless. Should be possible with edits to the class

        if(color == color0) {
            undeployedPieceShapeIDs0.push_back(PieceShapeToInt(pieceShape));
        } else if(color == color1) {
            undeployedPieceShapeIDs1.push_back(PieceShapeToInt(pieceShape));
        } else {
            std::cout << "Player does not play with the given color.\n";
            exit(1);
        }
    }

    void Player::RemoveUndeployedPieceShape(Color color, PieceShape pieceShape) {
        //TODO: Make this brancheless. Should be possible with edits to the class

        if(color == color0) {
            std::vector<int>::iterator iterator = std::find(undeployedPieceShapeIDs0.begin(), undeployedPieceShapeIDs0.end(), PieceShapeToInt(pieceShape));
            if(iterator != undeployedPieceShapeIDs0.end()) {
                undeployedPieceShapeIDs0.erase(iterator);
            } else {
                std::cout << "Player does not have the specified piece shape on his hand to remove.\n";
                exit(1);
            }
        } else if(color == color1) {
            std::vector<int>::iterator iterator = std::find(undeployedPieceShapeIDs1.begin(), undeployedPieceShapeIDs1.end(), PieceShapeToInt(pieceShape));
            if(iterator != undeployedPieceShapeIDs1.end()) {
                undeployedPieceShapeIDs1.erase(iterator);
            } else {
                std::cout << "Player does not have the specified piece shape on his hand to remove.\n";
                exit(1);
            }
        } else {
            std::cout << "Player does not play with the given color.\n";
            exit(1);
        }
    }
}  // namespace HokusBlokus::Blokus