#pragma once

#include "vec2i.hpp"

namespace HokusBlokus::Blokus::Optimization {
    /**
     * @brief A class representing a rectangle
     * 
     */
    class BoundingRect {
        /**
         * @brief Lower left corner of the rectangle
         * 
         */
        Vec2i minBounds;

        /**
         * @brief Upper right corner of the rectangle
         * 
         */
        Vec2i maxBounds;

    public:
        /**
        * @brief Constructs a new BoundingRect object
        * 
        */
        BoundingRect();

        /**
         * @brief Constructs a new BoundingRect object
         * 
         * @param minBounds Lower left corner of the rectangle
         * @param maxBounds Upper right corner of the rectangle
         */
        BoundingRect(const Vec2i& minBounds, const Vec2i& maxBounds);

        /**
         * @brief Gets the lower left corner of the rectangle
         * 
         * @return The lower left corner of the rectangle
         */
        const Vec2i& GetMinBounds();

        /**
         * @brief Sets the lower left corner of the rectangle
         * 
         * @param minBounds The lower left corner of the rectangle
         */
        void SetMinBounds(const Vec2i& minBounds);

        /**
         * @brief Gets the upper right corner of the rectangle
         * 
         * @return The upper right corner of the rectangle
         */
        const Vec2i& GetMaxBounds();

        /**
         * @brief Sets the upper right corner of the rectangle
         * 
         * @param maxBounds The upper right corner of the rectangle
         */
        void SetMaxBounds(const Vec2i& maxBounds);
    };
}