#pragma once

#include <vector>

#include "board.hpp"
#include "move.hpp"

namespace HokusBlokus::Blokus {
    class Gamestate {
    private:
        Board board;
        Color currentPlayerColor;
        std::vector<Move> performedMoves;
        unsigned int turn;
        unsigned int startingPieceShapeID;

    public:
        Gamestate();

        void InitStartingGameState();

        Board& GetBoard();

        Color GetCurrentPlayerColor();

        std::vector<Move> GetPossibleMoves();

        void PerformMove(const Move& move);
    };
}  // namespace Blokus