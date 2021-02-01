#pragma once

#include <boost/dynamic_bitset.hpp>

namespace HokusBlokus::PBM {
    /**
     * @brief A simple class that represents a PBM image
     * 
     */
    class PBMImage {
        /**
         * @brief Width and height of the image
         * 
         */
        unsigned int width, height;

        /**
         * @brief Data of the image
         * 
         */
        boost::dynamic_bitset<> data;

    public:
        /**
         * @brief Constructs a new PBMImage from data
         * 
         * @param width The width of the image
         * @param height The height of the image
         * @param data The data of the image
         */
        PBMImage(unsigned int width, unsigned int height, boost::dynamic_bitset<> data);

        /**
         * @brief Gets the width of the image
         * 
         * @return unsigned int 
         */
        unsigned int GetWidth() const;

        /**
         * @brief Gets the height of the image
         * 
         * @return unsigned int 
         */
        unsigned int GetHeight() const;

        /**
         * @brief Gets the data of the image
         * 
         * @return const boost::dynamic_bitset<>& 
         */
        const boost::dynamic_bitset<>& GetData() const;
    };
}  // namespace HokusBlokus::PBM