#include "pbmloader.hpp"

namespace HokusBlokus::PBM {
    PBMImage PBMLoader::ReadPBMToVector(std::string path) {
        unsigned int width = 0;
        unsigned int height = 0;
        //Read bitmmap metadata. We will only load the P4 format
        std::ifstream inputStream(path, std::ios::binary);
        std::string line;
        int lineCount = 0;
        while (std::getline(inputStream, line) && width == height == 0) {
            if (lineCount == 0 && line != "P4") {
                std::cout << "Unable to read pbm file. Expected type P4.\n";
                std::exit(1);
            } else if(line[0] != '#') {
                line.find(' ');
            }
            lineCount++;
        }

        //Read bitmap data
        std::ifstream inputStreamBinary(path, std::ios::binary);
        boost::dynamic_bitset<> data = boost::dynamic_bitset<>(width * height);

        char byte;
        int bitCount = 0;
        while (inputStreamBinary.get(byte) && bitCount < width * height) {
            for (int i = 7; i >= 0; i--) {
                if ((byte >> i) & 1) {
                    data[bitCount % width, bitCount / width];
                }
                bitCount++;
            }
        }

        return PBMImage(width, height, data);
    }
}  // namespace HokusBlokus::PBM