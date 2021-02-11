#pragma once

#include <chrono>

#include "gameState.hpp"

namespace HokusBlokus::Blokus::Benchmark {
    /**
     * @brief A simple benchmark mmethod to test getPossibleMoves()
     * 
     * @param benchmarkTime The time in ms to benchmark
     */
    void benchmarkGPM(unsigned int benchmarkTime);

    /**
     * @brief Simple perft benchmark
     * 
     * @param depth Depth to fully search to
     */
    void perft(int depth);

    /**
     * @brief Simple recursive perft call
     * 
     * @param depth Current perft depth
     * @param gameState Current GameState
     */
    long perftRecursive(int depth, GameState& gameState);
}