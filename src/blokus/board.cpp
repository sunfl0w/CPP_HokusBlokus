#include "board.hpp"

namespace HokusBlokus::Blokus {
    Board::Board() {
        std::array<std::bitset<484>, 4> bitsets = std::array<std::bitset<484>, 4>();
    }

    void Board::InitStartingBoard() {
        for(int i = 0; i < 4; i++) {
            bitsets[i][0] = 1;
            bitsets[i][21] = 1;
            bitsets[i][462] = 1;
            bitsets[i][483] = 1;
        }
    }

    std::bitset<484>& Board::GetBitset(Color color) {
        return bitsets[ColorToUInt(color)];
    }
}  // namespace HokusBlokus::Blokus