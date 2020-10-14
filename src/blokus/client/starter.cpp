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
#include "logic.hpp"
#include "blokusClient.hpp"


using namespace HokusBlokus::Blokus;
using namespace HokusBlokus::Blokus::Benchmark;
using namespace HokusBlokus::Blokus::AI;
using namespace HokusBlokus::Blokus::Client;

int main(int argc, char *argv[]) {
    std::cout << "Hello There\n";

    HokusBlokus::Blokus::PieceManager::Init();

    /*std::cout << "Starting client\n";
    Logic logic = Logic();
    BlokusClient blokusClient = BlokusClient(&logic);
    blokusClient.Start(argc, argv);*/

    BenchmarkGPM(10000);

    /*GameState gameState = GameState();
    gameState.InitStartingGameState();
    srand(time(NULL));
    while(!gameState.IsGameOver()) {
        Debug::DrawGameState(gameState);
        std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
        gameState.PerformMove(possibleMoves[rand() % possibleMoves.size()]);

        if(gameState.GetTurn() > 12) {
            int i = 0;
        }
    }*/
    return 0;
}