#include "piece.hpp"

namespace HokusBlokus::Blokus {
    Piece::Piece(std::vector<PieceBitmask> pieceBitmasks) {
        std::vector<PieceBitmask> shapeBitmasks = std::vector<PieceBitmask>();
        std::vector<PieceBitmask> cornerBitmasks = std::vector<PieceBitmask>();
        std::vector<PieceBitmask> edgeBitmasks = std::vector<PieceBitmask>();

        for (PieceBitmask pieceBitmask : pieceBitmasks) {
            if(pieceBitmask.GetMaskType() == MaskType::Shape) {
                shapeBitmasks.push_back(pieceBitmask);
            } else if(pieceBitmask.GetMaskType() == MaskType::Corner) {
                cornerBitmasks.push_back(pieceBitmask);
            } else {
                edgeBitmasks.push_back(pieceBitmask);
            }
        }

        shapeBitmasks = FilterDuplicateBitmasks(shapeBitmasks);
        cornerBitmasks = FilterDuplicateBitmasks(cornerBitmasks);
        edgeBitmasks = FilterDuplicateBitmasks(edgeBitmasks);

        for(unsigned int i = 0; i < shapeBitmasks.size(); i++) {
            std::array<PieceBitmask, 3> bitmaskComplement = {shapeBitmasks[i], cornerBitmasks[i], edgeBitmasks[i]};
            pieceBitmaskComplements.push_back(bitmaskComplement);
        }
    }

    const std::vector<std::array<PieceBitmask, 3>>& Piece::GetPieceBitmaskComplements() const {
        return pieceBitmaskComplements;
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