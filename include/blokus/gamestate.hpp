#pragma once

#include <vector>

#include "board.hpp"
#include "move.hpp"

namespace Blokus {
    class Gamestate {
    private:
        Board board;
        unsigned int turn;

    public:
        Gamestate();

        Board& GetBoard();

        std::vector<Move> GetPossibleMoves();

        void PerformMove(const Move& move);
    };
}  // namespace Blokus