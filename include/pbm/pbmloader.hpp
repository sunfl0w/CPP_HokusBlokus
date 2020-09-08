#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "pbmimage.hpp"

namespace HokusBlokus::PBM {
    class PBMLoader {
    public:
        static PBMImage LoadPBM(std::string path);

    private:
        PBMLoader();

        static std::vector<std::string> SplitStringIntoWords(std::string string, char delimiter);
    };
}  // namespace HokusBlokus::PBM