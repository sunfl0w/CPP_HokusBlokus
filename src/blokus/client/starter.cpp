#include <bitset>
#include <filesystem>
#include <iostream>
#include <string>

#include "benchmark.hpp"
#include "board.hpp"
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
#include "logger.hpp"


using namespace HokusBlokus::Blokus;
using namespace HokusBlokus::Blokus::Benchmark;
using namespace HokusBlokus::Blokus::AI;
using namespace HokusBlokus::Blokus::Client;
using namespace HokusBlokus::Util;

int main(int argc, char *argv[]) {
    Logger::getInstance() << "Hello There\n";

    HokusBlokus::Blokus::PieceManager::Init(std::filesystem::path(argv[0]).parent_path());

    Logger::getInstance() << "Starting client\n";
    Logic logic = Logic();
    BlokusClient blokusClient = BlokusClient(&logic);

    try {
    blokusClient.Start(argc, argv);
    } catch(...) {
        Logger::getInstance() << "How could this happen. We are better than this\n";
    }

    //BenchmarkGPM(100000);

    /*GameState gameState = GameState();
    gameState.InitStartingGameState();
    gameState.Draw();
    srand(time(NULL));
    while(!gameState.IsGameOver()) {
        std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
        gameState.PerformMove(possibleMoves[rand() % possibleMoves.size()]);

        gameState.Draw();
        int x = 0;
    }*/
    return 0;
}