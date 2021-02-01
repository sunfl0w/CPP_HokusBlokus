#pragma once

#include <string>

namespace HokusBlokus::Blokus {
    /**
     * @brief This class represents a Color of a Player
     * 
     */
    enum class Color {
        BLUE = 0,
        YELLOW = 1,
        RED = 2,
        GREEN = 3,
    };

    /**
     * @brief Converts a Color to int
     * 
     * @param color The Color to convert
     * @return int 
     */
    int ColorToInt(Color color);

    /**
     * @brief Converts a Color to String
     * 
     * @param color The Color to convert
     * @return std::string 
     */
    std::string ColorToString(Color color);

    /**
     * @brief Converts an int to Color
     * 
     * @param value The int to convert
     * @return Color 
     */
    Color IntToColor(int value);
}