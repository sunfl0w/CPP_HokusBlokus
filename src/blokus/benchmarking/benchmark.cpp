#include "benchmark.hpp"

using namespace HokusBlokus::Blokus;

namespace HokusBlokus::Blokus::Benchmarking {
    void BenchmarkGPM(unsigned int benchmarkTime) {
        srand(time(NULL));

        int count = 0;
        int gamesPlayed = 0;
        Gamestate gamestate = Gamestate();
        gamestate.InitStartingGamestate();

        std::cout << "Starting to benchmark GPM\n";

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkTime) {
            if (gamestate.IsGameOver()) {
                gamesPlayed++;
                gamestate = Gamestate();
                gamestate.InitStartingGamestate();
            }
            std::vector<Move> possibleMoves = gamestate.GetPossibleMoves();
            gamestate.PerformMove(possibleMoves[rand() % possibleMoves.size()]);

            count++;
        }
        std::cout << "Searched possible moves on random gamestates " << count << " times in " << benchmarkTime << "ms"
                  << " || "
                  << "Random games played: " << gamesPlayed << std::endl;
    }
}