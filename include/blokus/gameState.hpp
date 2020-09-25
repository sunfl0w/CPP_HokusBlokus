#pragma once

#include <vector>

#include "vec2i.hpp"
#include "moveType.hpp"
#include "board.hpp"
#include "move.hpp"
#include "player.hpp"
#include "piece.hpp"
#include "pieceShape.hpp"
#include "pieceManager.hpp"
#include "pieceBitmask.hpp"
#include "colorQueue.hpp"
#include "boundingRectOptimizer.hpp"

using namespace HokusBlokus::Blokus::Optimization;

namespace HokusBlokus::Blokus {
    class GameState {
    private:
        Board board;
        Player player0;
        Player player1;
        ColorQueue colorQueue;
        std::vector<Move> performedMoves;
        int turn;
        PieceShape startingPieceShape;
        BoundingRectOptimizer boundingRectOptimizer;

    public:
        GameState();

        void InitStartingGameState();

        Board& GetBoard();

        Color GetCurrentColor() const;

        Player& GetCurrentPlayer();

        std::vector<Move>& GetPerformedMoves();

        Move& GetLastPerfromedMove();

        int GetTurn() const;

        PieceShape GetStartingPieceShape() const;

        std::vector<Move> GetPossibleMoves();

        void PerformMove(const Move& move);

        void UndoLastMove();

        bool IsGameOver() const;
    };
}  // namespace Blokus