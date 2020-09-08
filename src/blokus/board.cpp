#include "board.hpp"

namespace HokusBlokus::Blokus {
    Board::Board() {
        blueSet = std::bitset<484>();
        redSet = std::bitset<484>();
        greenSet = std::bitset<484>();
        yellowSet = std::bitset<484>();
    }
}