#pragma once

#include <vector>
#include <array>
#include <bitset>
#include <algorithm>

#include "pieceBitmask.hpp"
#include "pieceBitmaskComplement.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief Class representing a Blokus Piece
     * 
     */
    class Piece {
    private:
        /**
         * @brief List of all bitmask complements of the Piece
         * 
         */
        std::vector<PieceBitmaskComplement> pieceBitmaskComplements;

    public:
        /**
         * @brief Constructs a new Piece
         * 
         * @param pieceBitmaskComplements The list of all complements defining that piece
         */
        Piece(std::vector<PieceBitmaskComplement> pieceBitmaskComplements);

        /**
         * @brief Gets the list of all complements defining that piece
         * 
         * @return const std::vector<PieceBitmaskComplement>& 
         */
        const std::vector<PieceBitmaskComplement>& GetPieceBitmaskComplements() const;

    private:
        /**
         * @brief Filters duplicate complements
         * 
         * @param pieceBitmaskComplements List of complements to filter
         * @return std::vector<PieceBitmaskComplement> 
         */
        std::vector<PieceBitmaskComplement> FilterDuplicateBitmaskComplements(const std::vector<PieceBitmaskComplement>& pieceBitmaskComplements) const;
    };
}