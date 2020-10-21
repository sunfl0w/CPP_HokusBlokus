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
#include "logger.hpp"


using namespace HokusBlokus::Blokus;
using namespace HokusBlokus::Blokus::Benchmark;
using namespace HokusBlokus::Blokus::AI;
using namespace HokusBlokus::Blokus::Client;
using namespace HokusBlokus::Util;

int main(int argc, char *argv[]) {
    //Logger logger = Logger(std::filesystem::current_path().string());
    Logger logger = Logger("/run/media/sunfl0w/Common Storage/Projekte/CPP/Socha/Blokus/CPP_HokusBlokus");

    logger << "Hello There\n";

    HokusBlokus::Blokus::PieceManager::Init();

    std::cout << "Starting client\n";
    Logic logic = Logic();
    BlokusClient blokusClient = BlokusClient(&logic, &logger);
    blokusClient.Start(argc, argv);

    //BenchmarkGPM(1000);

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