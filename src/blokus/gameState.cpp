#include "gameState.hpp"

namespace HokusBlokus::Blokus {
    GameState::GameState() : player0(Color::BLUE, Color::RED), player1(Color::YELLOW, Color::GREEN) {
        board = Board();
        colorQueue = ColorQueue();
        performedMoves = std::vector<Move>();
        turn = 0;
    }

    void GameState::InitStartingGameState() {
        board = Board();
        board.InitStartingBoard();
        player0 = Player(Color::BLUE, Color::RED);
        player0.PopulateUndeployedPieces();
        player1 = Player(Color::YELLOW, Color::GREEN);
        player1.PopulateUndeployedPieces();
        colorQueue = ColorQueue();
        performedMoves = std::vector<Move>();
        turn = 0;

        srand(time(NULL));
        startingPieceShape = PieceShape::MONOMINO;
        while (PieceShapeToUInt(startingPieceShape) == 0 || PieceShapeToUInt(startingPieceShape) == 16) {
            startingPieceShape = UIntToPieceShape(rand() % 12 + 9);
        }
    }

    Board& GameState::GetBoard() {
        return board;
    }

    Color GameState::GetCurrentColor() const {
        return colorQueue.GetCurrentColor();
    }

    Player& GameState::GetCurrentPlayer() {
        if (GetCurrentColor() == Color::BLUE || GetCurrentColor() == Color::RED) {
            return player0;
        } else {
            return player1;
        }
    }

    std::vector<Move>& GameState::GetPerformedMoves() {
        return performedMoves;
    }

    Move& GameState::GetLastPerfromedMove() {
        return performedMoves[performedMoves.size() - 1];
    }

    unsigned int GameState::GetTurn() const {
        return turn;
    }

    PieceShape GameState::GetStartingPieceShape() const {
        return startingPieceShape;
    }

    std::vector<Move> GameState::GetPossibleMoves() {
        std::vector<Move> possibleMoves = std::vector<Move>();

        std::bitset<484> occupiedMask = board.GetBitmask(Color::BLUE) | board.GetBitmask(Color::YELLOW) | board.GetBitmask(Color::RED) | board.GetBitmask(Color::GREEN);

        std::vector<unsigned int> playablePieces;
        if (turn < 4) {
            playablePieces = {PieceShapeToUInt(startingPieceShape)};
        } else {
            playablePieces = GetCurrentPlayer().GetUndeployedPieceShapeIDs(GetCurrentColor());
        }

        for (unsigned int pieceID : playablePieces) {
            Piece piece = PieceManager::GetPiece(UIntToPieceShape(pieceID));
            unsigned int complementNumber = 0;
            std::vector<std::array<PieceBitmask, 3>> pieceBitmaskComplements = piece.GetPieceBitmaskComplements();
            for (int complementNumber = 0; complementNumber < pieceBitmaskComplements.size(); complementNumber++) {
                unsigned int maxShiftX = 20 - pieceBitmaskComplements[complementNumber][0].GetMaskDimensions().x;
                unsigned int maxShiftY = 20 - pieceBitmaskComplements[complementNumber][0].GetMaskDimensions().y;

                #ifdef BOUNDING_BOX_OPTIMIZATION

                // Bounding box optimized method
                for (unsigned int y = 0; y <= maxShiftY; y++) {
                    for (unsigned int x = 0; x <= maxShiftX; x++) {
                        // corner test -> Shape test -> edge test

                        if ((pieceBitmaskComplements[complementNumber][1].GetBitmask() << (x + y * 22) & board.GetBitmask(GetCurrentColor())).any() &&
                            (pieceBitmaskComplements[complementNumber][0].GetBitmask() << (x + y * 22) & occupiedMask).none() &&
                            (pieceBitmaskComplements[complementNumber][2].GetBitmask() << (x + y * 22) & board.GetBitmask(GetCurrentColor())).none()) {
                            possibleMoves.push_back(Move(Vec2ui(x, y), UIntToPieceShape(pieceID), complementNumber, GetCurrentColor(), MoveType::SetMove));
                        }
                    }
                }
                #else

                // Brute Force method
                for (unsigned int y = 0; y <= maxShiftY; y++) {
                    for (unsigned int x = 0; x <= maxShiftX; x++) {
                        // corner test -> Shape test -> edge test

                        if ((pieceBitmaskComplements[complementNumber][1].GetBitmask() << (x + y * 22) & board.GetBitmask(GetCurrentColor())).any() &&
                            (pieceBitmaskComplements[complementNumber][0].GetBitmask() << (x + y * 22) & occupiedMask).none() &&
                            (pieceBitmaskComplements[complementNumber][2].GetBitmask() << (x + y * 22) & board.GetBitmask(GetCurrentColor())).none()) {
                            possibleMoves.push_back(Move(Vec2ui(x, y), UIntToPieceShape(pieceID), complementNumber, GetCurrentColor(), MoveType::SetMove));
                        }
                    }
                }
                #endif
            }
        }

        if (turn >= 4 && possibleMoves.size() > 0) {
            possibleMoves.push_back(Move(Vec2ui(0, 0), PieceShape::MONOMINO, 0, GetCurrentColor(), MoveType::SkipMove));
        }

        if (possibleMoves.empty()) {
            possibleMoves.push_back(Move(Vec2ui(0, 0), PieceShape::MONOMINO, 0, GetCurrentColor(), MoveType::PassMove));
        }

        return possibleMoves;
    }

    void GameState::PerformMove(const Move& move) {
        // Moves will not be checked for validity to improve perfromance

        if (move.GetMoveType() == MoveType::SetMove) {
            board.GetBitmask(GetCurrentColor()) |=
                (PieceManager::GetPiece(move.GetPieceShape()).GetPieceBitmaskComplements()[move.GetComplementNumber()][0].GetBitmask() << (move.GetDestination().x + move.GetDestination().y * 22));
            GetCurrentPlayer().RemoveUndeployedPieceShape(move.GetColor(), move.GetPieceShape());
        }

        if (move.GetMoveType() == MoveType::PassMove) {
            colorQueue.RemoveColor(move.GetColor());
        }

        turn++;
        performedMoves.push_back(move);
        colorQueue.Advance();
    }

    void GameState::UndoLastMove() {
        // Last perfromed move will not be checked for validity to improve perfromance

        Move lastMove = performedMoves[performedMoves.size() - 1];

        if (lastMove.GetMoveType() == MoveType::SetMove) {
            std::bitset<484> bitmask = PieceManager::GetPiece(lastMove.GetPieceShape()).GetPieceBitmaskComplements()[lastMove.GetComplementNumber()][0].GetBitmask();
            board.GetBitmask(lastMove.GetColor()) &= (bitmask << (lastMove.GetDestination().x + lastMove.GetDestination().y * 22)).flip();
            GetCurrentPlayer().AddUndeployedPieceShape(lastMove.GetColor(), lastMove.GetPieceShape());
        }

        if (lastMove.GetMoveType() == MoveType::PassMove) {
            colorQueue.AddColor(lastMove.GetColor());
        }

        turn--;
        performedMoves.pop_back();
        colorQueue.Revert();
    }

    bool GameState::IsGameOver() const {
        if (turn >= 100 || !colorQueue.HasActivePlayers()) {
            return true;
        }
        return false;
    }
}  // namespace HokusBlokus::Blokus