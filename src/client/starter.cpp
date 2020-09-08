#include <iostream>
#include <string>

#include "pbmimage.hpp"
#include "pbmloader.hpp"

int main() {
    std::cout << "Hello There\n";
    //Test load pbm
    HokusBlokus::PBM::PBMImage image = HokusBlokus::PBM::PBMLoader::LoadPBM("resources/BlokusPieces.pbm");

    //Drawing the image
    for (int y = 0; y < image.GetHeight(); y++) {
        std::string line;
        for (int x = 0; x < image.GetWidth(); x++) {
            if (image.GetData()[x + y * image.GetWidth()] == 1) {
                line.append("0");
            } else {
                line.append("1");
            }
        }
        std::cout << line << "\n";
    }
    return 0;
}