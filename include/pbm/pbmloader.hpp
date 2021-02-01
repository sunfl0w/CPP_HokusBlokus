#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "pbmimage.hpp"

namespace HokusBlokus::PBM {
    /**
     * @brief A class for loading PBM images
     * 
     */
    class PBMLoader {
    public:
        /**
         * @brief Loads a PBM immage
         * 
         * @param path The path of the image to load
         * @return PBMImage 
         */
        static PBMImage LoadPBM(std::string path);

    private:
        /**
         * @brief Constructs a new PBMLoader
         * 
         */
        PBMLoader();

        /**
         * @brief Splits a String into Sunstrings by a given delimiter
         * 
         * @param string The String to split
         * @param delimiter The delimiter to use
         * @return std::vector<std::string> 
         */
        static std::vector<std::string> SplitStringIntoWords(std::string string, char delimiter);
    };
}  // namespace HokusBlokus::PBM