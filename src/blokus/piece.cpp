#include "piece.hpp"

namespace HokusBlokus::Blokus {
    Piece::Piece(std::vector<PieceBitmask> pieceBitmasks) {
        for (PieceBitmask pieceBitmask : pieceBitmasks) {
            if(pieceBitmask.GetMaskType() == MaskType::Shape) {
                pieceShapeBitmasks.push_back(pieceBitmask);
            } else if(pieceBitmask.GetMaskType() == MaskType::Corner) {
                pieceCornerBitmasks.push_back(pieceBitmask);
            } else {
                pieceEdgeBitmasks.push_back(pieceBitmask);
            }
        }

        pieceShapeBitmasks = FilterDuplicateBitmasks(pieceShapeBitmasks);
        pieceCornerBitmasks = FilterDuplicateBitmasks(pieceCornerBitmasks);
        pieceEdgeBitmasks = FilterDuplicateBitmasks(pieceEdgeBitmasks);
    }

    const std::vector<PieceBitmask>& Piece::GetPieceShapeBitmasks() const {
        return pieceShapeBitmasks;
    }

    const std::vector<PieceBitmask>& Piece::GetPieceCornerBitmasks() const {
        return pieceCornerBitmasks;
    }

    const std::vector<PieceBitmask>& Piece::GetPieceEdgeBitmasks() const {
        return pieceEdgeBitmasks;
    }

    std::vector<PieceBitmask> Piece::FilterDuplicateBitmasks(const std::vector<PieceBitmask>& pieceBitmasks) const {
        std::vector<PieceBitmask> nonDuplicatePieceBitmasks = std::vector<PieceBitmask>();

        for (PieceBitmask pieceBitmask : pieceBitmasks) {
            if (std::find(nonDuplicatePieceBitmasks.begin(), nonDuplicatePieceBitmasks.end(), pieceBitmask) == nonDuplicatePieceBitmasks.end()) {
                nonDuplicatePieceBitmasks.push_back(pieceBitmask);
            }
        }
        return nonDuplicatePieceBitmasks;
    }
}  // namespace HokusBlokus::Blokus