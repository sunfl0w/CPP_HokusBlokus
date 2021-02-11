#include "benchmark.hpp"

using namespace HokusBlokus::Blokus;

namespace HokusBlokus::Blokus::Benchmark {
    void benchmarkGPM(unsigned int benchmarkTime) {
        srand(time(NULL));

        int count = 0;
        int gamesPlayed = 0;
        GameState gameState = GameState();
        gameState.InitStartingGameState();

        std::cout << "Starting to benchmark GPM\n";

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkTime) {
            if (gameState.IsGameOver()) {
                gamesPlayed++;
                gameState = GameState();
                gameState.InitStartingGameState();
            }
            std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
            gameState.PerformMove(possibleMoves[rand() % possibleMoves.size()]);

            count++;
        }
        std::cout << "Searched possible moves on random game states " << count << " times in " << benchmarkTime << "ms"
                  << " || "
                  << "Random games played: " << gamesPlayed << "\n";
    }

    void perft(int depth) {
        GameState gameState = GameState();
        gameState.InitStartingGameState();
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        long nodes = perftRecursive(depth, gameState);
        int time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::cout << "Perft to depth " << depth << " finished in " << time << " milliseconds with " << nodes << " visited" << "\n";
    }

    long perftRecursive(int depth, GameState& gameState) {
        if(depth == 0) {
            return 1;
        }

        long nodes = 0;

        std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
        for(Move move : possibleMoves) {
            gameState.PerformMove(move);
            nodes += perftRecursive(depth - 1, gameState);
            gameState.UndoLastMove();
        }
        return nodes;
    }
}