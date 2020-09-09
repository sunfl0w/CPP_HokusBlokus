#include "player.hpp"

namespace HokusBlokus::Blokus {
    Player::Player(Color color0, Color color1) : color0(color0), color1(color1) {
    }

    void Player::PopulateUndeployedPieces() {
        undeployedPieceShapeIDs0 = std::vector<unsigned int>();
        undeployedPieceShapeIDs1 = std::vector<unsigned int>();
        for (int i = 0; i < 21; i++) {
            undeployedPieceShapeIDs0.push_back(i);
            undeployedPieceShapeIDs1.push_back(i);
        }
    }

    const std::vector<unsigned int>& Player::GetUndeployedPieceShapeIDs(Color color) const {
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

    void Player::RemovePieceShapeID0(Color color, unsigned int id) {
        //TODO: Make this brancheless. Should be possible with edits to the class
        if(color == color0) {
            std::vector<unsigned int>::iterator iterator = std::find(undeployedPieceShapeIDs0.begin(), undeployedPieceShapeIDs0.end(), id);
            if(iterator != undeployedPieceShapeIDs0.end()) {
                undeployedPieceShapeIDs0.erase(iterator);
            } else {
                std::cout << "Player does not have the specified piece shape on his hand to remove.\n";
                exit(1);
            }
        } else if(color == color1) {
            std::vector<unsigned int>::iterator iterator = std::find(undeployedPieceShapeIDs1.begin(), undeployedPieceShapeIDs1.end(), id);
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