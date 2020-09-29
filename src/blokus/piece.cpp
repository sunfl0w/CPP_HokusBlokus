#include "piece.hpp"

namespace HokusBlokus::Blokus {
    Piece::Piece(std::vector<PieceBitmaskComplement> pieceBitmaskComplements) {
        this->pieceBitmaskComplements = FilterDuplicateBitmaskComplements(pieceBitmaskComplements);
    }

    const std::vector<PieceBitmaskComplement>& Piece::GetPieceBitmaskComplements() const {
        return pieceBitmaskComplements;
    }

    std::vector<PieceBitmaskComplement> Piece::FilterDuplicateBitmaskComplements(const std::vector<PieceBitmaskComplement>& pieceBitmaskComplements) const {
        std::vector<PieceBitmaskComplement> nonDuplicateComplements = std::vector<PieceBitmaskComplement>();

        for (PieceBitmaskComplement pieceBitmaskComplement : pieceBitmaskComplements) {
            if (std::find(nonDuplicateComplements.begin(), nonDuplicateComplements.end(), pieceBitmaskComplement) == nonDuplicateComplements.end()) {
                nonDuplicateComplements.push_back(pieceBitmaskComplement);
            }
        }
        return nonDuplicateComplements;
    }
}  // namespace HokusBlokus::Blokus