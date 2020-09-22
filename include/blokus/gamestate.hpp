#pragma once

#include <vector>

#include "vec2ui.hpp"
#include "moveType.hpp"
#include "board.hpp"
#include "move.hpp"
#include "player.hpp"
#include "piece.hpp"
#include "pieceshape.hpp"
#include "piecemanager.hpp"
#include "piecebitmask.hpp"
#include "debugging.hpp"

namespace HokusBlokus::Blokus {
    class Gamestate {
    private:
        Board board;
        Player player0;
        Player player1;
        Color currentColor;
        std::vector<Move> performedMoves;
        unsigned int turn;
        unsigned int startingPieceShapeID;

    public:
        Gamestate();

        void InitStartingGameState();

        Board& GetBoard();

        Color GetCurrentColor();

        const Player& GetCurrentPlayer();

        std::vector<Move> GetPossibleMoves();

        void PerformMove(const Move& move);

        void UndoLastMove();
    };
}  // namespace Blokus