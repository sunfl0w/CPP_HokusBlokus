#pragma once

#include <bitset>
#include <sstream>

#include "vec2i.hpp"
#include "maskType.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief This class represents a PieceBitmask
     * 
     */
    class PieceBitmask {
    private:
        /**
         * @brief The bitmask of the Piece
         * 
         */
        std::bitset<484> bitmask;

        /**
         * @brief Dimensions of the bitmask
         * 
         */
        Vec2i maskDimensions;

        /**
         * @brief The type of the bitmask
         * 
         */
        MaskType maskType;

    public:
        /**
         * @brief Constructs a new empty PieceBitmask
         * 
         */
        PieceBitmask();
        
        /**
         * @brief Constructs a new PieceBitmask
         * 
         * @param bitmask Bitmask to use
         * @param maskType MaskType to use
         */
        PieceBitmask(std::bitset<484> bitmask, MaskType maskType);

        /**
         * @brief Equality operator
         * 
         * @param other Other PieceBitmask
         * @return true When equal
         * @return false When not equal
         */
        bool operator==(const PieceBitmask& other) const;

        /**
         * @brief Gets the bitmask
         * 
         * @return const std::bitset<484>& 
         */
        const std::bitset<484>& GetBitmask() const;

        /**
         * @brief Gets the bitmask dimensions
         * 
         * @return const Vec2i& 
         */
        const Vec2i& GetMaskDimensions() const;
        
        /**
         * @brief Gets the MaskType
         * 
         * @return MaskType 
         */
        MaskType GetMaskType() const;

        /**
         * @brief Draws a PieceBitmask to a String for debugging
         * 
         * @return std::string 
         */
        std::string Draw() const;

    private:
        /**
         * @brief Computes the dimensions of the bitmask
         * 
         * @param bitmask The bitmask to get the size of
         * @return Vec2i 
         */
        Vec2i ComputeMaskDimensions(const std::bitset<484>& bitmask) const;
    };
}