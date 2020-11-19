#include "board.hpp"

namespace HokusBlokus::Blokus {
    Board::Board() {
        std::array<std::bitset<484>, 4> colorBitmasks;
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
        return colorBitmasks[ColorToInt(color)];
    }

    void Board::SetBitmask(Color color, std::bitset<484> bitmask) {
        colorBitmasks[ColorToInt(color)] = bitmask;
    }

    std::string Board::Draw() {
        std::stringstream stream;
        stream << "Board----------\n";
        for (int y = 0; y < 22; y++) {
            std::string line;
            for (int x = 0; x < 22; x++) {
                if (x + 22 * y == 0 || x + 22 * y == 21 || x + 22 * y == 462 || x + 22 * y == 483) {
                    line += "C";
                } else {
                    if (GetBitmask(Color::BLUE)[x + 22 * y]) {
                        line += "B";
                    } else if (GetBitmask(Color::YELLOW)[x + 22 * y]) {
                        line += "Y";
                    } else if (GetBitmask(Color::RED)[x + 22 * y]) {
                        line += "R";
                    } else if (GetBitmask(Color::GREEN)[x + 22 * y]) {
                        line += "G";
                    } else {
                        line += " ";
                    }
                }
            }
            stream << line << "\n";
        }
        stream << "Board----------\n";
        return stream.str();
    }
}  // namespace HokusBlokus::Blokus