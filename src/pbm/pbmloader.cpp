#include "pbmloader.hpp"

namespace HokusBlokus::PBM {
    PBMImage PBMLoader::ReadPBMToVector(std::string path) {
        unsigned int width, height;
        //Rad bitmmap metadata


        //Read bitmap data
        std::ifstream inputStream(path, std::ios::binary);
        boost::dynamic_bitset<> data = boost::dynamic_bitset<>(width * height); 

        char byte;
        int bitCount = 0;
        while(inputStream.get(byte)) {
            for(int i = 7; i >= 0; i--) {
                if((byte >> i) & 1) {
                    data[bitCount % width, bitCount / width];
                }
                bitCount++;
            }
        }

        return PBMImage(width, height, data);
    }
}