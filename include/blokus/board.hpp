#pragma once

#include <bitset>

namespace HokusBlokus::Blokus {
    class Board {
    private:
        std::bitset<484> blueSet;
        std::bitset<484> redSet;
        std::bitset<484> greenSet;
        std::bitset<484> yellowSet;

    public:
        Board();
    };
}  // namespace Blokus