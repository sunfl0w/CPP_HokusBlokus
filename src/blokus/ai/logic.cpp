#include "logic.hpp"

using namespace HokusBlokus::Util;

namespace HokusBlokus::Blokus::AI {
    Logic::Logic() {}

    Logic::~Logic() {}

    HokusBlokus::Blokus::Move Logic::GetNextMove(HokusBlokus::Blokus::GameState currentGameState, int ownPlayerID) {
        Logger::getInstance() << "Using C++ fallback GetNextMove(). Probably no logic was defined.\n";
        srand(time(NULL));
        std::vector<HokusBlokus::Blokus::Move> possibleMoves = currentGameState.GetPossibleMoves();
        return possibleMoves[rand() % possibleMoves.size()];
    }

    void Logic::OnGameEnd(int winningPlayerID) {
        Logger::getInstance() << "Using C++ fallback OnGameEnd(). Probably no logic was defined.\n";
        Logger::getInstance() << "Winning player has the ID: " + std::to_string(winningPlayerID) + "\n";
    }
}  // namespace AI