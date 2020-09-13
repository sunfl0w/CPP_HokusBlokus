#include "helpers.hpp"

namespace HokusBlokus::Blokus::Helpers {
    void DrawBitsets(std::bitset<484> bitset) {
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
    }
}  // namespace HokusBlokus::Blokus::Helpers