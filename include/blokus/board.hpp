#pragma once

#include <array>
#include <bitset>
#include <sstream>

#include "color.hpp"

namespace HokusBlokus::Blokus {
    class Board {
    private:
        // Order: Blue, Yellow, Red, Green
        std::array<std::bitset<484>, 4> colorBitmasks;

    public:
        Board();

        void InitStartingBoard();

        std::bitset<484>& GetBitmask(Color color);

        void SetBitmask(Color color, std::bitset<484> bitmask);

        std::string Draw();
    };
}  // namespace HokusBlokus::Blokus