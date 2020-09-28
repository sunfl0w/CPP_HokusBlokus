#include <bitset>
#include <filesystem>
#include <iostream>
#include <string>

#include "benchmark.hpp"
#include "board.hpp"
#include "debug.hpp"
#include "gameState.hpp"
#include "move.hpp"
#include "pbmimage.hpp"
#include "pbmloader.hpp"
#include "pieceBitmask.hpp"
#include "pieceManager.hpp"
#include "pieceShape.hpp"
#include "vec2i.hpp"

using namespace HokusBlokus::Blokus;
using namespace HokusBlokus::Blokus::Benchmark;

int main() {
    std::cout << "Hello There\n";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';

    HokusBlokus::Blokus::PieceManager::Init();

    BenchmarkGPM(10000);

    /*HokusBlokus::Blokus::PieceManager::Init();
    Gamestate gamestate = Gamestate();
    gamestate.InitStartingGamestate();
    srand(time(NULL));
    while(!gamestate.IsGameOver()) {
        std::vector<Move> possibleMoves = gamestate.GetPossibleMoves();
        gamestate.PerformMove(possibleMoves[rand() % possibleMoves.size()]);
        Debugging::DrawGamestate(gamestate);
    }*/
    return 0;
}