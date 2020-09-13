#include "gamestate.hpp"

namespace HokusBlokus::Blokus {
    Gamestate::Gamestate() : player0(Color::BLUE, Color::RED), player1(Color::YELLOW, Color::GREEN) {
        board = Board();
        currentPlayerColor = Color::BLUE;
        performedMoves = std::vector<Move>();
        turn = 0;
    }

    void Gamestate::InitStartingGameState() {
        board = Board();
        board.InitStartingBoard();
        player0 = Player(Color::BLUE, Color::RED);
        player1 = Player(Color::YELLOW, Color::GREEN);
        currentPlayerColor = Color::BLUE;
        performedMoves = std::vector<Move>();
        turn = 0;

        srand(time(NULL));
        startingPieceShapeID = rand() % 21;
    }

    Board& Gamestate::GetBoard() {
        return board;
    }

    Color Gamestate::GetCurrentPlayerColor() {
        return currentPlayerColor;
    }

    std::vector<Move> Gamestate::GetPossibleMoves() {
        std::bitset occupiedSet = board.GetBitset(Color::BLUE) & board.GetBitset(Color::YELLOW) & board.GetBitset(Color::RED) & board.GetBitset(Color::GREEN);

        unsigned int minShift;
        unsigned int maxShift;

        for (int i = 0; i < 21; i++) {
            for (int s = minShift; s < maxShift; s++) {

            }
        }
    }

    void Gamestate::PerformMove(const Move& move) {
        //Moves will not be checked for validity to improve perfromance
    }
}  // namespace HokusBlokus::Blokus