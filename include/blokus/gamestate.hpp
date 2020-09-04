#pragma once

#include "board.hpp"
#include "move.hpp"

#include <vector>

namespace Blokus {
    class Gamestate {
    private:
    Board board;
    unsigned int turn;

    public:
    Gamestate();

    Board& GetBoard();

    std::vector<Move> GetPossibleMoves();
    };
}