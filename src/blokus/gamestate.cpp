#include "gamestate.hpp"

namespace HokusBlokus::Blokus {
    Gamestate::Gamestate() {
    }

    Board& Gamestate::GetBoard() {
        return board;
    }

    std::vector<Move> Gamestate::GetPossibleMoves() {
        
    }

    void Gamestate::PerformMove(const Move& move) {
        //Moves will not be checked for validity to improve perfromance
    }
}