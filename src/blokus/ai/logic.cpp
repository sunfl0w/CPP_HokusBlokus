#include "logic.hpp"

using namespace HokusBlokus::Util;

namespace HokusBlokus::Blokus::AI {
    Logic::Logic() {}

    Logic::~Logic() {}

    HokusBlokus::Blokus::Move Logic::GetNextMove(HokusBlokus::Blokus::GameState currentGameState, int ownPlayerID) {
        Logging::logger << "Using C++ fallback GetNextMove(). Probably no logic was defined.\n";
        srand(time(NULL));
        std::vector<HokusBlokus::Blokus::Move> possibleMoves = currentGameState.GetPossibleMoves();
        return possibleMoves[rand() % possibleMoves.size()];
    }

    void Logic::OnGameEnd(int winningPlayerID) {
        Logging::logger << "Using C++ fallback OnGameEnd(). Probably no logic was defined.\n";
        Logging::logger << "Winning player has the ID: " + std::to_string(winningPlayerID) + "\n";
    }
}  // namespace AI