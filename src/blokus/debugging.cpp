#include "debugging.hpp"

namespace HokusBlokus::Blokus {
    void Debugging::DrawBitset(std::bitset<484> bitset) {
        std::cout << "----------\n";
        for (int y = 0; y < 22; y++) {
            std::string line;
            for (int x = 0; x < 22; x++) {
                if (bitset[x + 22 * y]) {
                    line += "1";
                } else {
                    line += "0";
                }
            }
            std::cout << line << "\n";
        }
        std::cout << "----------\n";
    }
}