#pragma once

#include <array>
#include <vector>

#include "maskType.hpp"
#include "pieceBitmask.hpp"
#include "pieceRotation.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief A complement od bitmasks that represent a Piece with a given rotation and its mirror state
     * 
     */
    class PieceBitmaskComplement {
        /**
         * @brief Complementary bitmasks
         * 
         */
        std::array<PieceBitmask, 3> bitmasks;

        /**
         * @brief Rotation of the represented Piece
         * 
         */
        PieceRotation rotation;

        /**
         * @brief Mirror/flipped state of the Piece represented by the complement
         * 
         */
        bool flipped;

    public:
        /**
         * @brief Construct a new empty PieceBitmaskComplement
         * 
         */
        PieceBitmaskComplement();

        /**
         * @brief Construct a new PieceBitmaskComplement
         * 
         * @param bitmasks List of bitmasks that compose the complement
         * @param rotation Rotation of the complement
         * @param flipped  Flipped state of the complement
         */
        PieceBitmaskComplement(std::array<PieceBitmask, 3> bitmasks, PieceRotation rotation, bool flipped);

        /**
         * @brief Equality operator
         * 
         * @param other Other PieceBitmaskComplement
         * @return true When equal
         * @return false When not equal
         */
        bool operator==(const PieceBitmaskComplement& other);

        /**
         * @brief Gets the PieceBitmask of type of the complement
         * 
         * @param maskType Type of bitmask to get
         * @return const PieceBitmask& 
         */
        const PieceBitmask& GetBitmask(MaskType maskType) const;

        /**
         * @brief Gets the PieceRotation of the complement
         * 
         * @return PieceRotation 
         */
        PieceRotation GetRotation() const;

        /**
         * @brief Gets the flipped state of the complement
         * 
         * @return true When flipped
         * @return false When not flipped
         */
        bool IsFlipped() const;
    };
}  // namespace HokusBlokus::Blokus