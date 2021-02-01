#pragma once

namespace HokusBlokus::Blokus {
    /**
     * @brief A simple vector of two integers
     * 
     */
    class Vec2i {
    public:
        /**
         * @brief The values of the vector
         * 
         */
        int x, y;

        /**
         * @brief Constructs a new Vec2i
         * 
         */
        Vec2i();
        
        /**
         * @brief Constructs a new Vec2i
         * 
         * @param x The x value of the vector
         * @param y The y value of the vector
         */
        Vec2i(int x, int y);

        /**
         * @brief Equality operator
         * 
         * @param other The other vector
         * @return true When equal
         * @return false When not equal
         */
        bool operator==(const Vec2i& other) const;
    };
}  // namespace Blokus