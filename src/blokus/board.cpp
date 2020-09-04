#include "board.hpp"

namespace Blokus {
    Board::Board() {
        blueSet = std::bitset<400>();
        redSet = std::bitset<400>();
        greenSet = std::bitset<400>();
        yellowSet = std::bitset<400>();
    }
}