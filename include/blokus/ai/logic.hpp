#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "gameState.hpp"
#include "move.hpp"
#include "player.hpp"
#include "color.hpp"

namespace HokusBlokus::Blokus::AI {
    /**
     * @brief This class defines some virtual methods for creating AIs for the game of Blokus.
     * 
     */
    class Logic {
    public:
        /**
         * @brief Constructs a new Logic.
         * 
         */
        Logic();

        /**
         * @brief Destroys a Logic.
         * 
         */
        virtual ~Logic();

        /**
         * @brief Gets the next Move to play. In this method the AI hast to be implemented.
         * 
         * @param currentGameState The GameState to get the next Move for.
         * @param ownPlayerID The ID of the Player that is played by the AI.
         * @return The next move that should be played.
         */
        virtual HokusBlokus::Blokus::Move GetNextMove(HokusBlokus::Blokus::GameState currentGameState, int ownPlayerID);

        /**
         * @brief Will be executed when a game of Blokus ends.
         * 
         * @param winningPlayerID The ID of the Player that won.
         */
        virtual void OnGameEnd(int winningPlayerID);
    };
} // namespace Piranhas::Logic