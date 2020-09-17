#include "gamestate.hpp"

namespace HokusBlokus::Blokus {
    Gamestate::Gamestate() : player0(Color::BLUE, Color::RED), player1(Color::YELLOW, Color::GREEN) {
        board = Board();
        currentColor = Color::BLUE;
        performedMoves = std::vector<Move>();
        turn = 0;
    }

    void Gamestate::InitStartingGameState() {
        board = Board();
        board.InitStartingBoard();
        player0 = Player(Color::BLUE, Color::RED);
        player0.PopulateUndeployedPieces();
        player1 = Player(Color::YELLOW, Color::GREEN);
        player1.PopulateUndeployedPieces();
        currentColor = Color::BLUE;
        performedMoves = std::vector<Move>();
        turn = 0;

        srand(time(NULL));
        startingPieceShapeID = 0;
        while (startingPieceShapeID == 0 || startingPieceShapeID == 16) {
            startingPieceShapeID = rand() % 12 + 9;
        }
    }

    Board& Gamestate::GetBoard() { return board; }

    Color Gamestate::GetCurrentColor() { return currentColor; }

    const Player& Gamestate::GetCurrentPlayer() {
        if (currentColor == Color::BLUE || currentColor == Color::RED) {
            return player0;
        } else {
            return player1;
        }
    }

    std::vector<Move> Gamestate::GetPossibleMoves() {
        std::vector<Move> possibleMoves = std::vector<Move>();
        possibleMoves.push_back(Move(Vec2ui(0, 0), PieceShape::MONOMINO, Color::BLUE, MoveType::SkipMove));
        std::bitset<484> occupiedMask = board.GetBitmask(Color::BLUE) & board.GetBitmask(Color::YELLOW) & board.GetBitmask(Color::RED) & board.GetBitmask(Color::GREEN);

        std::vector<unsigned int> playablePieces;
        if (turn < 4) {
            playablePieces = {startingPieceShapeID};
        } else {
            playablePieces = GetCurrentPlayer().GetUndeployedPieceShapeIDs(currentColor);
        }

        for (unsigned int pieceID : playablePieces) {
            Piece piece = PieceManager::GetPiece(UIntToPieceShape(pieceID));
            for (std::array<PieceBitmask, 3> pieceBitmaskComplement : piece.GetPieceBitmaskComplements()) {
                unsigned int maxShiftX = 20 - pieceBitmaskComplement[0].GetMaskDimensions().x;
                unsigned int maxShiftY = 20 - pieceBitmaskComplement[0].GetMaskDimensions().y;

                for (unsigned int y = 0; y <= maxShiftY; y++) {
                    for (unsigned int x = 0; x <= maxShiftX; x++) {
                        // Shape test -> corner test -> edge test
                        if ((pieceBitmaskComplement[0].GetBitmask() << (x + y * 22) & occupiedMask).none() &&
                            (pieceBitmaskComplement[1].GetBitmask() << (x + y * 22) & board.GetBitmask(currentColor)).any() &&
                            (pieceBitmaskComplement[2].GetBitmask() << (x + y * 22) & board.GetBitmask(currentColor)).none()) {
                            possibleMoves.push_back(Move(Vec2ui(x, y), UIntToPieceShape(pieceID), currentColor, MoveType::SetMove));
                        }
                    }
                }
            }
        }
        return possibleMoves;
    }

    void Gamestate::PerformMove(const Move& move) {
        // Moves will not be checked for validity to improve perfromance
    }
}  // namespace HokusBlokus::Blokus