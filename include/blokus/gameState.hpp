#pragma once

#include <vector>
#include <sstream>

#include "vec2i.hpp"
#include "moveType.hpp"
#include "board.hpp"
#include "move.hpp"
#include "player.hpp"
#include "piece.hpp"
#include "pieceShape.hpp"
#include "pieceManager.hpp"
#include "pieceBitmask.hpp"
#include "pieceBitmaskComplement.hpp"
#include "boundingRectOptimizer.hpp"
#include "logger.hpp"

using namespace HokusBlokus::Blokus::Optimization;

namespace HokusBlokus::Blokus {
    /**
     * @brief This class represents a valid game state of the game blokus
     * 
     */
    class GameState {
    private:
        /**
         * @brief The Board
         * 
         */
        Board board;

        /**
         * @brief The first Player
         * 
         */
        Player player0;

        /**
         * @brief The second Player
         * 
         */
        Player player1;

        /**
         * @brief Performed Moves on the GameState
         * 
         */
        std::vector<Move> performedMoves;

        /**
         * @brief Current turn
         * 
         */
        int turn;

        /**
         * @brief The starting PieceShape
         * 
         */
        PieceShape startingPieceShape;

        /**
         * @brief The bounding rect optimizer
         * 
         */
        BoundingRectOptimizer boundingRectOptimizer;

    public:
        /**
         * @brief Constructs a new GameState
         * 
         */
        GameState();

        /**
         * @brief Initializes a GameState so ist can be used for playing
         * 
         */
        void InitStartingGameState();

        /**
         * @brief Gets the Board of the GameState
         * 
         * @return Board& 
         */
        Board& GetBoard();

        /**
         * @brief Gets the current Color
         * 
         * @return Color 
         */
        Color GetCurrentColor() const;

        /**
         * @brief Gets the current Player
         * 
         * @return Player& 
         */
        Player& GetCurrentPlayer();

        /**
         * @brief Gets the Player of a given Color
         * 
         * @param color The Color of the Player
         * @return Player& 
         */
        Player& GetPlayerWithColor(Color color);

        /**
         * @brief Gets the list of all performed Moves on the GameState
         * 
         * @return std::vector<Move>& 
         */
        std::vector<Move>& GetPerformedMoves();

        /**
         * @brief Gets the last perfromed Move
         * 
         * @return Move& 
         */
        Move& GetLastPerfromedMove();

        /**
         * @brief Sets the last performed Move
         * 
         * @param move The Move to set
         */
        void SetLastPerformedMove(Move move);

        /**
         * @brief Gets the current turn
         * 
         * @return int 
         */
        int GetTurn() const;

        /**
         * @brief Sets the current turn
         * 
         * @param turn The turn count to set to
         */
        void SetTurn(int turn);

        /**
         * @brief Gets the PieceShape of the starting Piece
         * 
         * @return PieceShape
         */
        PieceShape GetStartingPieceShape() const;

        /**
         * @brief Sets the PieceShape of the starting Piece
         * 
         * @param pieceShape The PieceShape to set
         */
        void SetStartingPieceShape(PieceShape pieceShape);

        /**
         * @brief Gets the possible Moves for the GameState
         * 
         * @return std::vector<Move> 
         */
        std::vector<Move> GetPossibleMoves();

        /**
         * @brief Performms a given Move on the GameState
         * 
         * @param move The Move to perform
         */
        void PerformMove(const Move& move);

        /**
         * @brief Reverts the last move that was performed on the GameState
         * 
         */
        void UndoLastMove();

        /**
         * @brief Returns whether a game given by the GameState is over
         * 
         * @return true When the game is over
         * @return false When the game is still ongoing
         */
        bool IsGameOver() const;

        /**
         * @brief Draws a GameState to a String for debugging
         * 
         * @return std::string 
         */
        std::string Draw();
    };
}  // namespace Blokus