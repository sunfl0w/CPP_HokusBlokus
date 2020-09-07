#pragma once

#include "pbmimage.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace HokusBlokus::PBM {
    class PBMLoader {
    public:
        static PBMImage ReadPBMToVector(std::string path);
    };
}  // namespace HokusBlokus::PBM