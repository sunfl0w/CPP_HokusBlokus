#include "piece.hpp"

namespace HokusBlokus::Blokus {
    Piece::Piece(std::vector<PieceBitset> pieceBitsets) {
        for (PieceBitset pieceBitset : pieceBitsets) {
            if(pieceBitset.GetMaskType() == MaskType::Shape) {
                pieceShapeBitsets.push_back(pieceBitset);
            } else if(pieceBitset.GetMaskType() == MaskType::Corner) {
                pieceCornerBitsets.push_back(pieceBitset);
            } else {
                pieceEdgeBitsets.push_back(pieceBitset);
            }
        }

        pieceShapeBitsets = FilterDuplicateBitsets(pieceShapeBitsets);
        pieceCornerBitsets = FilterDuplicateBitsets(pieceCornerBitsets);
        pieceEdgeBitsets = FilterDuplicateBitsets(pieceEdgeBitsets);
    }

    const std::vector<PieceBitset>& Piece::GetPieceShapeBitsets() const {
        return pieceShapeBitsets;
    }

    const std::vector<PieceBitset>& Piece::GetPieceCornerBitsets() const {
        return pieceCornerBitsets;
    }

    const std::vector<PieceBitset>& Piece::GetPieceEdgeBitsets() const {
        return pieceEdgeBitsets;
    }

    std::vector<PieceBitset> Piece::FilterDuplicateBitsets(const std::vector<PieceBitset>& pieceBitsets) const {
        std::vector<PieceBitset> nonDuplicatePieceBitsets = std::vector<PieceBitset>();

        for (PieceBitset pieceBitset : pieceBitsets) {
            if (std::find(nonDuplicatePieceBitsets.begin(), nonDuplicatePieceBitsets.end(), pieceBitset) == nonDuplicatePieceBitsets.end()) {
                nonDuplicatePieceBitsets.push_back(pieceBitset);
            }
        }
        return nonDuplicatePieceBitsets;
    }
}  // namespace HokusBlokus::Blokus