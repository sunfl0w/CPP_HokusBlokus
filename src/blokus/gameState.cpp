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
        while (PieceShapeToInt(startingPieceShape) == 0 || PieceShapeToInt(startingPieceShape) == 16) {
            startingPieceShape = IntToPieceShape(rand() % 12 + 9);
        }
    }

    Board& GameState::GetBoard() {
        return board;
    }

    Color GameState::GetCurrentColor() const {
        return colorQueue.GetCurrentColor();
    }

    Player& GameState::GetCurrentPlayer() {
        if (player0.GetColors()[0] == GetCurrentColor() || player0.GetColors()[1] == GetCurrentColor()) {
            return player0;
        } else {
            return player1;
        }
    }

    Player& GameState::GetPlayerWithColor(Color color) {
        if (player0.GetColors()[0] == color || player0.GetColors()[1] == color) {
            return player0;
        } else {
            return player1;
        }
    }

    ColorQueue& GameState::GetColorQueue() {
        return colorQueue;
    }

    std::vector<Move>& GameState::GetPerformedMoves() {
        return performedMoves;
    }

    Move& GameState::GetLastPerfromedMove() {
        return performedMoves[performedMoves.size() - 1];
    }

    void GameState::SetLastPerformedMove(Move move) {
        if (performedMoves.empty()) {
            performedMoves.push_back(move);
        } else {
            performedMoves[performedMoves.size() - 1] = move;
        }
    }

    int GameState::GetTurn() const {
        return turn;
    }

    void GameState::SetTurn(int turn) {
        this->turn = turn;
    }

    PieceShape GameState::GetStartingPieceShape() const {
        return startingPieceShape;
    }

    void GameState::SetStartingPieceShape(PieceShape pieceShape) {
        startingPieceShape = pieceShape;
    }

    std::vector<Move> GameState::GetPossibleMoves() {
        std::vector<Move> possibleMoves = std::vector<Move>();

        std::bitset<484> occupiedMask = board.GetBitmask(Color::BLUE) | board.GetBitmask(Color::YELLOW) | board.GetBitmask(Color::RED) | board.GetBitmask(Color::GREEN);

        std::vector<int> playablePieces;
        if (turn < 4) {
            playablePieces = {PieceShapeToInt(startingPieceShape)};
        } else {
            playablePieces = GetCurrentPlayer().GetUndeployedPieceShapeIDs(GetCurrentColor());
        }

        int minShiftX = 0;
        int minShiftY = 0;
        int maxShiftX = 0;
        int maxShiftY = 0;

        for (int pieceID : playablePieces) {
            Piece piece = PieceManager::GetPiece(IntToPieceShape(pieceID));
            for (unsigned int complementNumber = 0; complementNumber < piece.GetPieceBitmaskComplements().size(); complementNumber++) {
                // Bounding rect search optimization
                BoundingRect moveSearchRect = boundingRectOptimizer.GetBoundingRect(GetCurrentColor());

                minShiftX = std::max(moveSearchRect.GetMinBounds().x - piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetMaskDimensions().x - 1, 0);
                minShiftY = std::max(moveSearchRect.GetMinBounds().y - piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetMaskDimensions().y - 1, 0);
                maxShiftX = std::min(moveSearchRect.GetMaxBounds().x + 1, 20 - piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetMaskDimensions().x);
                maxShiftY = std::min(moveSearchRect.GetMaxBounds().y + 1, 20 - piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetMaskDimensions().y);

                for (int y = minShiftY; y <= maxShiftY; y++) {
                    for (int x = minShiftX; x <= maxShiftX; x++) {
                        // corner test -> Shape test -> edge test
                        // 1
                        if ((piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Corner).GetBitmask() & board.GetBitmask(GetCurrentColor())).any() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetBitmask() & occupiedMask).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Edge).GetBitmask() & board.GetBitmask(GetCurrentColor())).none()) {
                            possibleMoves.emplace_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), GetCurrentColor(), MoveType::SetMove, complementNumber));
                        }

                        //Other versions for testing. Hard to test as the code might include bugs
                        // 2
                        /*if ((piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Corner).GetBitmask() & board.GetBitmask(GetCurrentColor())).any() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Edge).GetBitmask() & board.GetBitmask(GetCurrentColor())).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetBitmask() & occupiedMask).none()) {
                            possibleMoves.emplace_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), GetCurrentColor(), MoveType::SetMove, complementNumber));
                        }*/

                        // 3
                        /*if ((piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetBitmask() & occupiedMask).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Edge).GetBitmask() & board.GetBitmask(GetCurrentColor())).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Corner).GetBitmask() & board.GetBitmask(GetCurrentColor())).any()) {
                            possibleMoves.emplace_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), GetCurrentColor(), MoveType::SetMove, complementNumber));
                        }*/

                        // 4
                        /*if ((piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetBitmask() & occupiedMask).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Corner).GetBitmask() & board.GetBitmask(GetCurrentColor())).any() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Edge).GetBitmask() & board.GetBitmask(GetCurrentColor())).none()) {
                            possibleMoves.emplace_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), GetCurrentColor(), MoveType::SetMove, complementNumber));
                        }*/

                        // 5
                        /*if ((piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Edge).GetBitmask() & board.GetBitmask(GetCurrentColor())).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetBitmask() & occupiedMask).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Corner).GetBitmask() & board.GetBitmask(GetCurrentColor())).any()) {
                            possibleMoves.emplace_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), GetCurrentColor(), MoveType::SetMove, complementNumber));
                        }*/

                        // 6
                        /*if ((piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Edge).GetBitmask() & board.GetBitmask(GetCurrentColor())).none() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Corner).GetBitmask() & board.GetBitmask(GetCurrentColor())).any() &&
                            (piece.GetPieceBitmaskComplements()[complementNumber].GetBitmask(MaskType::Shape).GetBitmask() & occupiedMask).none()) {
                            possibleMoves.emplace_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), GetCurrentColor(), MoveType::SetMove, complementNumber));
                        }*/
                    }
                }
            }
        }

        if (turn >= 4 && possibleMoves.size() > 0) {
            possibleMoves.emplace_back(Move(Vec2i(0, 0), PieceShape::MONOMINO, GetCurrentColor(), MoveType::SkipMove, 0));
        }

        if (possibleMoves.empty()) {
            possibleMoves.emplace_back(Move(Vec2i(0, 0), PieceShape::MONOMINO, GetCurrentColor(), MoveType::PassMove, 0));
        }

        return possibleMoves;
    }

    void GameState::PerformMove(const Move& move) {
        // Moves will not be checked for validity to improve perfromance

        if (move.GetMoveType() == MoveType::SetMove) {
            board.GetBitmask(GetCurrentColor()) |= (PieceManager::GetPiece(move.GetPieceShape()).GetPieceBitmaskComplements()[move.GetComplementNumber()].GetBitmask(MaskType::Shape).GetBitmask()
                                                    << (move.GetDestination().x + move.GetDestination().y * 22));
            GetCurrentPlayer().RemoveUndeployedPieceShape(move.GetColor(), move.GetPieceShape());

            if (GetCurrentPlayer().GetUndeployedPieceShapeIDs(move.GetColor()).empty()) {
                colorQueue.RemoveColor(move.GetColor());
            }
        }

        if (move.GetMoveType() == MoveType::PassMove) {
            colorQueue.RemoveColor(move.GetColor());
        }

        // Optimize bounding rects for the move search
        boundingRectOptimizer.OptimizeBoundingRectOfColor(GetCurrentColor(), GetBoard());

        turn++;
        performedMoves.push_back(move);
        colorQueue.Advance();
    }

    void GameState::UndoLastMove() {
        // Last perfromed move will not be checked for validity to improve perfromance

        Move lastMove = performedMoves[performedMoves.size() - 1];

        if (lastMove.GetMoveType() == MoveType::SetMove) {
            std::bitset<484> bitmask = PieceManager::GetPiece(lastMove.GetPieceShape()).GetPieceBitmaskComplements()[lastMove.GetComplementNumber()].GetBitmask(MaskType::Shape).GetBitmask();
            board.GetBitmask(lastMove.GetColor()) &= (bitmask << (lastMove.GetDestination().x + lastMove.GetDestination().y * 22)).flip();
            GetPlayerWithColor(lastMove.GetColor()).AddUndeployedPieceShape(lastMove.GetColor(), lastMove.GetPieceShape());

            if (colorQueue.WasColorRemoved(lastMove.GetColor())) {
                colorQueue.AddColor(lastMove.GetColor());
            }
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