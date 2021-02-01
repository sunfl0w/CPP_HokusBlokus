#pragma once

#include <array>
#include <bitset>
#include <sstream>

#include "color.hpp"

namespace HokusBlokus::Blokus {
    class Board {
    private:
        /**
         * @brief Array of all color bitmasks. Order: Blue, Yellow, Red, Green
         * 
         */
        std::array<std::bitset<484>, 4> colorBitmasks;

    public:
        /**
         * @brief Constructs a new Board empty object
         * 
         */
        Board();

        /**
         * @brief Initializes a Board to be a valid starting board for a new game
         * 
         */
        void InitStartingBoard();

        /**
         * @brief Gets the Bitmask object for a given Color
         * 
         * @param color The Color to get the Bitmask of
         * @return std::bitset<484>& 
         */
        std::bitset<484>& GetBitmask(Color color);

        /**
         * @brief Sets the Bitmask object of a given Color
         * 
         * @param color The Color to set the Bitmask of
         * @param bitmask The Bitmask for setting
         */
        void SetBitmask(Color color, std::bitset<484> bitmask);

        /**
         * @brief Drwas a Board to a String. This is for easy debugging
         * 
         * @return std::string 
         */
        std::string Draw();
    };
}  // namespace HokusBlokus::Blokus