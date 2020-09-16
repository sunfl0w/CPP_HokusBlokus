#include <bitset>
#include <filesystem>
#include <iostream>
#include <string>

#include "pbmimage.hpp"
#include "pbmloader.hpp"
#include "piecemanager.hpp"
#include "pieceshape.hpp"
#include "vec2ui.hpp"

int main() {
    std::cout << "Hello There\n";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    //Test bitset manager
    HokusBlokus::Blokus::PieceManager::Init();

    HokusBlokus::Blokus::PieceShape shape = HokusBlokus::Blokus::PieceShape::DOMINO;
    HokusBlokus::Blokus::Piece piece = HokusBlokus::Blokus::PieceManager::GetPiece(shape);
    for (std::bitset<484> bitset : piece.GetPieceEdgeBitsets()) {
        std::cout << "----------\n";
        for (int y = 0; y < 22; y++) {
            std::string line;
            for (int x = 0; x < 22; x++) {
                if (bitset[x + 22 * y]) {
                    line += "1";
                } else {
                    line += "0";
                }
            }
            std::cout << line << "\n";
        }
        std::cout << "----------\n";
    }
    return 0;
}