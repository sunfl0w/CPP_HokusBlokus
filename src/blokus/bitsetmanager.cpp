#include "bitsetmanager.hpp"

namespace HokusBlokus::Blokus {
    void BitsetManager::LoadBitsets() {
        std::string pathToResources = "resources/";

        PBM::PBMImage pieceShapeBitmap = PBM::PBMLoader::LoadPBM(pathToResources + "BlokusPieceShapes.pbm");
        PBM::PBMImage pieceEdgeBitmap = PBM::PBMLoader::LoadPBM(pathToResources + "BlokusPieceEdges.pbm");
        PBM::PBMImage pieceCornerBitmap = PBM::PBMLoader::LoadPBM(pathToResources + "BlokusPieceCorners.pbm");

        pieceBitsets = PBMPiecesToFullScaleBitsets(pieceShapeBitmap, 5);
        pieceEdgeBitsets = PBMPiecesToFullScaleBitsets(pieceEdgeBitmap, 7);
        pieceCornerBitsets = PBMPiecesToFullScaleBitsets(pieceCornerBitmap, 7);
    }

    void BitsetManager::LoadPieceDimensions() {
        std::string pathToResources = "resources/";
        pieceDimensions = LoadDimensionListingFromFile(pathToResources + "BlokusPieceDimensions.txt");
        pieceEdgeCornerDimensions = LoadDimensionListingFromFile(pathToResources + "BlokusPieceEdgeCornerDimensions.txt");
    }

    std::bitset<484>& BitsetManager::GetBitsetOfPiece(PieceType pieceType) {
    }

    std::bitset<484>& BitsetManager::GetEdgeBitsetOfPiece(PieceType pieceType) {
    }

    std::bitset<484>& BitsetManager::GetCornerBitsetOfPiece(PieceType pieceType) {
    }

    Vec2ui& BitsetManager::GetDimensionsOfPiece(PieceType pieceType) {
    }

    Vec2ui& BitsetManager::GetEdgeDimensionsOfPiece(PieceType pieceType) {
    }

    std::vector<std::bitset<484>> BitsetManager::PBMPiecesToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize) {
        std::vector<std::bitset<484>> bitsets = std::vector<std::bitset<484>>();
        unsigned int minX = 0;
        unsigned int minY = 0;
        unsigned int maxX = pieceSize;
        unsigned int maxY = pieceSize;

        for (int i = 0; i < 21; i++) {
            std::bitset<484> bitset = std::bitset<484>();
            for (int x = minX; x < maxX; x++) {
                for (int y = minY; y < maxY; y++) {
                    bitset[x % pieceSize + (y % pieceSize) * 22] = bitmap.GetData()[x + y * bitmap.GetWidth()];
                }
            }
            bitsets.push_back(bitset);

            minX = maxX % bitmap.GetWidth();
            maxX = minX + pieceSize;

            if (minX == 0) {
                minY = maxY;
                maxY += pieceSize;
            }
        }
        return bitsets;
    }

    std::vector<Vec2ui> BitsetManager::LoadDimensionListingFromFile(std::string path) {
        std::ifstream inputStream(path);
        if (!inputStream) {
            std::cout << "Unable to open txt file.\n";
            std::exit(1);
        }

        std::string line;
        std::getline(inputStream, line);
        inputStream.close();

        std::vector<Vec2ui> pieceDimensions = std::vector<Vec2ui>();
        for (int i = 0; i < 21; i++) {
            pieceDimensions.push_back(Vec2ui(line[i * 2], line[i * 2 + 1]));
        }
        return pieceDimensions;
    }
}  // namespace HokusBlokus::Blokus