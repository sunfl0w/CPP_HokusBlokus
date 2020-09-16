#include "piece.hpp"

namespace HokusBlokus::Blokus {
    Piece::Piece(std::vector<std::bitset<484>> pieceShapeBitsets, std::vector<std::bitset<484>> pieceCornerBitsets, std::vector<std::bitset<484>> pieceEdgeBitsets, Vec2ui pieceShapeDimensions) : pieceShapeDimensions(pieceShapeDimensions), pieceEdgeCornerDimensions(pieceShapeDimensions.x + 2, pieceShapeDimensions.y + 2) {
        this->pieceShapeBitsets = FilterDuplicateBitsets(pieceShapeBitsets);
        this->pieceCornerBitsets = FilterDuplicateBitsets(pieceCornerBitsets);
        this->pieceEdgeBitsets = FilterDuplicateBitsets(pieceEdgeBitsets);
    }

    const std::vector<std::bitset<484>>& Piece::GetPieceShapeBitsets() const {
        return pieceShapeBitsets;
    }

    const std::vector<std::bitset<484>>& Piece::GetPieceCornerBitsets() const {
        return pieceCornerBitsets;
    }

    const std::vector<std::bitset<484>>& Piece::GetPieceEdgeBitsets() const {
        return pieceEdgeBitsets;
    }

    const Vec2ui& Piece::GetPieceShapeDimensions() const {
        return pieceShapeDimensions;
    }

    const Vec2ui& Piece::GetPieceEdgeCornerDimensions() const {
        return pieceEdgeCornerDimensions;
    }

    std::vector<std::bitset<484>> Piece::FilterDuplicateBitsets(const std::vector<std::bitset<484>>& pieceBitsets) const {
        std::vector<std::bitset<484>> nonDuplicatePieceBitsets = std::vector<std::bitset<484>>();

        for (std::bitset<484> pieceBitset : pieceBitsets) {
            if (std::find(nonDuplicatePieceBitsets.begin(), nonDuplicatePieceBitsets.end(), pieceBitset) == nonDuplicatePieceBitsets.end()) {
                nonDuplicatePieceBitsets.push_back(pieceBitset);
            }
        }
        return nonDuplicatePieceBitsets;
    }
}  // namespace HokusBlokus::Blokus