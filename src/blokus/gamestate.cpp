#include "gamestate.hpp"

namespace HokusBlokus::Blokus {
    Gamestate::Gamestate() {
        board = Board();
        currentPlayerColor = Color::BLUE;
        performedMoves = std::vector<Move>();
        turn = 0;
    }

    void Gamestate::InitStartingGameState() {
        board = Board();
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

    }

    void Gamestate::PerformMove(const Move& move) {
        //Moves will not be checked for validity to improve perfromance
    }
}