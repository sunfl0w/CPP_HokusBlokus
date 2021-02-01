#pragma once

#include <chrono>

#include "gameState.hpp"

namespace HokusBlokus::Blokus::Benchmark {
    /**
     * @brief A simple benchmark mmethod to test getPossibleMoves()
     * 
     * @param benchmarkTime The time in ms to benchmark
     */
    void BenchmarkGPM(unsigned int benchmarkTime);
}