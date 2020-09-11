#include <iostream>
#include <string>
#include <bitset>
#include <filesystem>

#include "pbmimage.hpp"
#include "pbmloader.hpp"
#include "globals.hpp"
#include "pieceshape.hpp"
#include "vec2ui.hpp"

int main() {
    std::cout << "Hello There\n";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    //Test bitset manager
    HokusBlokus::Blokus::InitBitsetManager();

    HokusBlokus::Blokus::PieceShape shape = HokusBlokus::Blokus::PieceShape::PENTO_S;
    std::bitset<484> bitset = HokusBlokus::Blokus::bitsetManager.GetShapeBitsetOfPiece(shape);
    HokusBlokus::Blokus::Vec2ui dimensions = HokusBlokus::Blokus::bitsetManager.GetDimensionsOfPiece(shape);
    HokusBlokus::Blokus::Vec2ui edgeDimensions = HokusBlokus::Blokus::bitsetManager.GetEdgeDimensionsOfPiece(shape);

    for(int y = 0; y < 22; y++) {
        std::string line;
        for(int x = 0; x < 22; x++) {
            if(bitset[x + 22 * y]) {
                line += "1";
            } else {
                line += "0";
            }
        }
        std::cout << line << "\n";
    }
    return 0;
}