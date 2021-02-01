#pragma once

#include <array>

#include "board.hpp"
#include "boundingRect.hpp"
#include "color.hpp"

namespace HokusBlokus::Blokus::Optimization {
	/**
     * @brief A class managing a bounding box for each color on a board
     * 
     */
	class BoundingRectOptimizer {
		/**
         * @brief Bounding boces for each color on the board
         * 
         */
		std::array<BoundingRect, 4> boundingRects;

	public:
		/**
        * @brief Constructs a new and empty BoundingRectOptimizer object
        * 
        */
		BoundingRectOptimizer();

        /**
         * @brief Returns the BoundingRect object of a given color
         * 
         * @param color The Color to get the BoundingRect of
         * @return const BoundingRect& 
         */
		const BoundingRect& GetBoundingRect(Color color);

        /**
         * @brief Optimizes the bounding boxes according to a valid board state
         * 
         * @param color The Color to optimize for
         * @param board The Board to optimize for
         */
		void OptimizeBoundingRectOfColor(Color color, Board board);
	};
}  // namespace HokusBlokus::Blokus::Optimization