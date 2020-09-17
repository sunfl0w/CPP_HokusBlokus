#include <bitset>
#include <filesystem>
#include <iostream>
#include <string>

#include "board.hpp"
#include "gamestate.hpp"
#include "move.hpp"
#include "pbmimage.hpp"
#include "pbmloader.hpp"
#include "piecebitmask.hpp"
#include "piecemanager.hpp"
#include "pieceshape.hpp"
#include "vec2ui.hpp"

using namespace HokusBlokus::Blokus;

int main() {
    std::cout << "Hello There\n";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    // Test bitset manager
    HokusBlokus::Blokus::PieceManager::Init();
    Gamestate gamestate = Gamestate();
    gamestate.InitStartingGameState();

    std::vector<Move> possibleMoves = gamestate.GetPossibleMoves();

    std::cout << "Possible moves: " << possibleMoves.size() << "\n";

    /*HokusBlokus::Blokus::PieceShape shape = HokusBlokus::Blokus::PieceShape::PENTO_S;
    HokusBlokus::Blokus::Piece piece = HokusBlokus::Blokus::PieceManager::GetPiece(shape);
    for (HokusBlokus::Blokus::PieceBitmask pieceBitmask : piece.GetPieceCornerBitmasks()) {
        std::bitset<484> bitset = pieceBitmask.GetBitmask();
        std::cout << "----------\n";
        std::cout << "DimX: " << pieceBitmask.GetMaskDimensions().x << " || DimY: " << pieceBitmask.GetMaskDimensions().y << "\n";
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
    }*/
    return 0;
}