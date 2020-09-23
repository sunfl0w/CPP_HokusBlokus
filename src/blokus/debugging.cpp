#include "debugging.hpp"

namespace HokusBlokus::Blokus {
    void Debugging::DrawBitset(std::bitset<484> bitset) {
        std::cout << "----------\n";
        for (int y = 0; y < 22; y++) {
            std::string line;
            for (int x = 0; x < 22; x++) {
                if (bitset[x + 22 * y]) {
                    line += "1";
                } else {
                    line += "0";
                }
            }
            std::cout << line << "\n";
        }
        std::cout << "----------\n";
    }

    void Debugging::DrawBoard(Board& board) {
        std::cout << "Board----------\n";
        for (int y = 0; y < 22; y++) {
            std::string line;
            for (int x = 0; x < 22; x++) {
                if (x + 22 * y == 0 || x + 22 * y == 21 || x + 22 * y == 462 || x + 22 * y == 483) {
                    line += "C";
                } else {
                    if (board.GetBitmask(Color::BLUE)[x + 22 * y]) {
                        line += "B";
                    } else if (board.GetBitmask(Color::YELLOW)[x + 22 * y]) {
                        line += "Y";
                    } else if (board.GetBitmask(Color::RED)[x + 22 * y]) {
                        line += "R";
                    } else if (board.GetBitmask(Color::GREEN)[x + 22 * y]) {
                        line += "G";
                    } else {
                        line += " ";
                    }
                }
            }
            std::cout << line << "\n";
        }
        std::cout << "Board----------\n";
    }

    void Debugging::DrawGamestate(Gamestate& gamestate) {
        std::cout << "Gamestate----------\n";
        std::cout << "Turn: " << gamestate.GetTurn() << "\n";
        std::cout << "CurrentColorID: " << ColorToUInt(gamestate.GetCurrentColor()) << "\n";
        std::cout << "StartPieceID: " << PieceShapeToUInt(gamestate.GetStartingPieceShape()) << "\n";
        if(gamestate.GetTurn() >= 1) {
            if(gamestate.GetLastPerfromedMove().GetMoveType() == MoveType::SetMove) {
                std::cout << "LastMoveType: SetMove" << "\n";
                std::cout << "LastMovePieceID: " << PieceShapeToUInt(gamestate.GetLastPerfromedMove().GetPieceShape()) << "\n";
                std::cout << "LastMoveDestPos: " << "X " << gamestate.GetLastPerfromedMove().GetDestination().x << " Y " << gamestate.GetLastPerfromedMove().GetDestination().y << "\n";
            } else {
                std::cout << "LastMoveType: SkipMove" << "\n";
            }
        }
        DrawBoard(gamestate.GetBoard());
        std::cout << "Gamestate----------\n";
    }
}  // namespace HokusBlokus::Blokus