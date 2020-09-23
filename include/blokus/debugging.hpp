#pragma once

#include <string>
#include <iostream>
#include <bitset>

#include "board.hpp"
#include "gamestate.hpp"

namespace HokusBlokus::Blokus {
    class Debugging {
        public:
        static void DrawBitset(std::bitset<484> bitset);

        static void DrawBoard(Board& board);

        static void DrawGamestate(Gamestate& gamestate);
    };
}