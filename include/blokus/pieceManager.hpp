#pragma once

#include <bitset>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "pieceShape.hpp"
#include "pieceBitmask.hpp"
#include "pieceBitmaskComplement.hpp"
#include "pbmimage.hpp"
#include "pbmloader.hpp"
#include "piece.hpp"
#include "logger.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief The PieceManager is a class managing all Pieces of Blokus. This class is needed so resources can be loaded from files
     * 
     */
    class PieceManager {
        /**
         * @brief List of all Blokus Pieces
         * 
         */
        static std::vector<Piece> pieces;

    public:
        /**
         * @brief Initializes the PieceManager
         * 
         * @param executionPath The path of the executable client. This will be used for resource loading
         */
        static void Init(const std::string& executionPath);

        /**
         * @brief Gets the Piece with a given PieceShape
         * 
         * @param pieceShape The PieceShape of the Piece to get
         * @return Piece& 
         */
        static Piece& GetPiece(PieceShape pieceShape);

    private:
        /**
         * @brief Constructs a new PieceManager
         * 
         */
        PieceManager();

        /**
         * @brief Loads all relevant resources into complements
         * 
         * @param pathToResources Path to loadable resources
         * @return std::array<std::array<PieceBitmaskComplement, 8>, 21> 
         */
        static std::array<std::array<PieceBitmaskComplement, 8>, 21> LoadBitmasks(const std::string& pathToResources);

        /**
         * @brief Converts PBM images to bitmasks
         * 
         * @param bitmap The PBM image to use
         * @param pieceSize The size maximum size of the Pieces
         * @param offset Offset to use when converting
         * @return std::array<std::bitset<484>, 21> 
         */
        static std::array<std::bitset<484>, 21> PBMPieceDataToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize, const Vec2i& offset);
    };
}  // namespace HokusBlokus::Blokus