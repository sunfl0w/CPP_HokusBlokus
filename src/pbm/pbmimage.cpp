#include "pbmimage.hpp"

namespace HokusBlokus::PBM {
    PBMImage::PBMImage(unsigned int width, unsigned int height, boost::dynamic_bitset<> data) : width(width), height(height), data(data) {
    }

    unsigned int PBMImage::GetWidth() {
        return width;
    }

    unsigned int PBMImage::GetHeight() {
        return height;
    }

    boost::dynamic_bitset<>& PBMImage::GetData() {
        return data;
    }
}  // namespace HokusBlokus::PBM