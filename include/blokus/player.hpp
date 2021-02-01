#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <algorithm>

#include "color.hpp"
#include "pieceShape.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief A class defining a Blokus Player
     * 
     */
    class Player {
        /**
         * @brief First Color of the Player
         * 
         */
        Color color0;

        /**
         * @brief Second Color of the Player
         * 
         */
        Color color1;

        /**
         * @brief List of all undeployed Pieces of the first Color
         * 
         */
        std::vector<int> undeployedPieceShapeIDs0;

        /**
         * @brief List of all undeployed Pieces of the second Color
         * 
         */
        std::vector<int> undeployedPieceShapeIDs1;

    public:
        /**
         * @brief Constructs a new Player
         * 
         * @param color0 The first Color of the Player
         * @param color1 The second Color of the Player
         */
        Player(Color color0, Color color1);

        /**
         * @brief Initializes the lists of undeployed piece IDs
         * 
         */
        void PopulateUndeployedPieces();

        /**
         * @brief Gets the Colors of the Player
         * 
         * @return std::array<Color, 2> 
         */
        std::array<Color, 2> GetColors();

        /**
         * @brief Gets the undeployed PieceShape IDs of a given Color
         * 
         * @param color The Color to get the undeployed PieceShape IDs of
         * @return const std::vector<int>& 
         */
        const std::vector<int>& GetUndeployedPieceShapeIDs(Color color) const;

        /**
         * @brief Adds a undeployed PieceShape of a given Color to the undeployed list
         * 
         * @param color The color of the Piece
         * @param pieceShape The shape of the Piece
         */
        void AddUndeployedPieceShape(Color color, PieceShape pieceShape);

        /**
         * @brief Removes a undeployed PieceShape of a given Color to the undeployed list
         * 
         * @param color The color of the Piece
         * @param pieceShape The shape of the Piece
         */
        void RemoveUndeployedPieceShape(Color color, PieceShape pieceShape);
    };
}  // namespace HokusBlokus::Blokus