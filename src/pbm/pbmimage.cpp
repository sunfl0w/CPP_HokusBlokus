#include "pbmimage.hpp"

namespace HokusBlokus::PBM {
    PBMImage::PBMImage(unsigned int width, unsigned int height, boost::dynamic_bitset<> data) : width(width), height(height), data(data) {
    }

    unsigned int PBMImage::GetWidth() const {
        return width;
    }

    unsigned int PBMImage::GetHeight() const {
        return height;
    }

    const boost::dynamic_bitset<>& PBMImage::GetData() const {
        return data;
    }
}  // namespace HokusBlokus::PBM