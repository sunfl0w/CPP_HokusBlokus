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

    int GameState::GetTurn() const {
        return turn;
    }

    PieceShape GameState::GetStartingPieceShape() const {
        return startingPieceShape;
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
            std::vector<std::array<PieceBitmask, 3>> pieceBitmaskComplements = piece.GetPieceBitmaskComplements();
            for (int complementNumber = 0; complementNumber < pieceBitmaskComplements.size(); complementNumber++) {
                
                // Bounding rect search optimization
                BoundingRect moveSearchRect = boundingRectOptimizer.GetBoundingRect(GetCurrentColor());

                minShiftX = std::max(moveSearchRect.GetMinBounds().x - pieceBitmaskComplements[complementNumber][0].GetMaskDimensions().x - 1, 0);
                minShiftY = std::max(moveSearchRect.GetMinBounds().y - pieceBitmaskComplements[complementNumber][0].GetMaskDimensions().y - 1, 0);
                maxShiftX = std::min(moveSearchRect.GetMaxBounds().x + 1, 20 - pieceBitmaskComplements[complementNumber][0].GetMaskDimensions().x);
                maxShiftY = std::min(moveSearchRect.GetMaxBounds().y + 1, 20 - pieceBitmaskComplements[complementNumber][0].GetMaskDimensions().y);

                for (int y = minShiftY; y <= maxShiftY; y++) {
                    for (int x = minShiftX; x <= maxShiftX; x++) {
                        // corner test -> Shape test -> edge test
                        if ((pieceBitmaskComplements[complementNumber][1].GetBitmask() << (x + y * 22) & board.GetBitmask(GetCurrentColor())).any() &&
                            (pieceBitmaskComplements[complementNumber][0].GetBitmask() << (x + y * 22) & occupiedMask).none() &&
                            (pieceBitmaskComplements[complementNumber][2].GetBitmask() << (x + y * 22) & board.GetBitmask(GetCurrentColor())).none()) {
                            possibleMoves.push_back(Move(Vec2i(x, y), IntToPieceShape(pieceID), complementNumber, GetCurrentColor(), MoveType::SetMove));
                        }
                    }
                }
            }
        }

        if (turn >= 4 && possibleMoves.size() > 0) {
            possibleMoves.push_back(Move(Vec2i(0, 0), PieceShape::MONOMINO, 0, GetCurrentColor(), MoveType::SkipMove));
        }

        if (possibleMoves.empty()) {
            possibleMoves.push_back(Move(Vec2i(0, 0), PieceShape::MONOMINO, 0, GetCurrentColor(), MoveType::PassMove));
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