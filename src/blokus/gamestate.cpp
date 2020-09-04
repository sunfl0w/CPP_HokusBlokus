#include "gamestate.hpp"

namespace Blokus {
    Gamestate::Gamestate() {
    }

    Board& Gamestate::GetBoard() {
        return board;
    }

    std::vector<Move> Gamestate::GetPossibleMoves() {

    }

    void Gamestate::PerformMove(const Move& move) {
        //Moves will not be chhecked for validity to improve perfromance
    }
}