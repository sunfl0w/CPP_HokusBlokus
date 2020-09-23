#include "board.hpp"

namespace HokusBlokus::Blokus {
    Board::Board() {
        std::array<std::bitset<484>, 4> colorBitmasks = std::array<std::bitset<484>, 4>();
    }

    void Board::InitStartingBoard() {
        for (int i = 0; i < 4; i++) {
            colorBitmasks[i][0] = 1;
            colorBitmasks[i][21] = 1;
            colorBitmasks[i][462] = 1;
            colorBitmasks[i][483] = 1;
        }
    }

    std::bitset<484>& Board::GetBitmask(Color color) {
        return colorBitmasks[ColorToUInt(color)];
    }
}  // namespace HokusBlokus::Blokus