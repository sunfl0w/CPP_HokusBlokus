#pragma once

#include <boost/dynamic_bitset.hpp>

namespace HokusBlokus::PBM {
    class PBMImage {
        unsigned int width, height;
        boost::dynamic_bitset<> data;

    public:
        PBMImage(unsigned int width, unsigned int height, boost::dynamic_bitset<> data);

        unsigned int GetWidth() const;

        unsigned int GetHeight() const;

        const boost::dynamic_bitset<>& GetData() const;
    };
}  // namespace HokusBlokus::PBM