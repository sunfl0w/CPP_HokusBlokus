#pragma once

#include <boost/dynamic_bitset.hpp>

namespace HokusBlokus::PBM {
    class PBMImage {
        unsigned int width, height;
        boost::dynamic_bitset<> data;

    public:
        PBMImage(unsigned int width, unsigned int height, boost::dynamic_bitset<> data);

        unsigned int GetWidth();

        unsigned int GetHeight();

        boost::dynamic_bitset<>& GetData();
    };
}  // namespace HokusBlokus::PBM