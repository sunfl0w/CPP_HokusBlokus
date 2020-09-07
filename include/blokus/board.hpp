#pragma once

#include <bitset>

namespace HokusBlokus::Blokus {
    class Board {
    private:
        std::bitset<400> blueSet;
        std::bitset<400> redSet;
        std::bitset<400> greenSet;
        std::bitset<400> yellowSet;

    public:
        Board();
    };
}  // namespace Blokus