#pragma once

#include <array>
#include <bitset>

#include "color.hpp"

namespace HokusBlokus::Blokus {
    class Board {
    private:
        //Order: Blue, Yellow, Red, Green
        std::array<std::bitset<484>, 4> bitsets;

    public:
        Board();

        void InitStartingBoard();

        std::bitset<484>& GetBitset(Color color);
    };
}  // namespace HokusBlokus::Blokus