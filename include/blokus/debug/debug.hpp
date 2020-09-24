#pragma once

#include <string>
#include <iostream>
#include <bitset>

#include "board.hpp"
#include "gameState.hpp"

namespace HokusBlokus::Blokus::Debug {
    void DrawBitset(std::bitset<484> bitset);

    void DrawBoard(Board& board);

    void DrawGameState(GameState& gameState);
}