#pragma once

namespace HokusBlokus::Blokus {
    /**
     * @brief Class representing MaskTypes for internal use
     * 
     */
    enum class MaskType {
        Shape,
        Corner,
        Edge,
    };

    /**
     * @brief Converts a MaskType to an int
     * 
     * @param maskType The MaskType to convert
     * @return int 
     */
    int MaskTypeToInt(MaskType maskType);

    /**
     * @brief Converts an int to a MaskType
     * 
     * @param value The int to convert
     * @return MaskType 
     */
    MaskType IntToMaskType(int value);
}