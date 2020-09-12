#include "bitsetmanager.hpp"

namespace HokusBlokus::Blokus {
    std::vector<std::bitset<484>> BitsetManager::pieceShapeBitsets = std::vector<std::bitset<484>>();
    std::vector<std::bitset<484>> BitsetManager::pieceEdgeBitsets = std::vector<std::bitset<484>>();
    std::vector<std::bitset<484>> BitsetManager::pieceCornerBitsets = std::vector<std::bitset<484>>();

    std::vector<Vec2ui> BitsetManager::pieceShapeDimensions = std::vector<Vec2ui>();
    std::vector<Vec2ui> BitsetManager::pieceEdgeCornerDimensions = std::vector<Vec2ui>();

    void BitsetManager::LoadBitsets() {
        std::string pathToResources = "resources/";

        PBM::PBMImage pieceShapeBitmap = PBM::PBMLoader::LoadPBM(pathToResources + "BlokusPieceShapes.pbm");
        PBM::PBMImage pieceEdgeBitmap = PBM::PBMLoader::LoadPBM(pathToResources + "BlokusPieceEdges.pbm");
        PBM::PBMImage pieceCornerBitmap = PBM::PBMLoader::LoadPBM(pathToResources + "BlokusPieceCorners.pbm");

        pieceShapeBitsets = PBMPieceDataToFullScaleBitsets(pieceShapeBitmap, 5, Vec2ui(1,1));
        pieceEdgeBitsets = PBMPieceDataToFullScaleBitsets(pieceEdgeBitmap, 7, Vec2ui(0,0));
        pieceCornerBitsets = PBMPieceDataToFullScaleBitsets(pieceCornerBitmap, 7, Vec2ui(0,0));
    }

    void BitsetManager::LoadPieceDimensions() {
        std::string pathToResources = "resources/";
        pieceShapeDimensions = LoadPieceDataDimensionsFromFile(pathToResources + "BlokusPieceDimensions.txt");
        pieceEdgeCornerDimensions = LoadPieceDataDimensionsFromFile(pathToResources + "BlokusPieceEdgeCornerDimensions.txt");
    }

    std::bitset<484>& BitsetManager::GetShapeBitsetOfPiece(PieceShape pieceShape) {
        return pieceShapeBitsets[PieceShapeToUInt(pieceShape)];
    }

    std::bitset<484>& BitsetManager::GetEdgeBitsetOfPiece(PieceShape pieceShape) {
        return pieceEdgeBitsets[PieceShapeToUInt(pieceShape)];
    }

    std::bitset<484>& BitsetManager::GetCornerBitsetOfPiece(PieceShape pieceShape) {
        return pieceCornerBitsets[PieceShapeToUInt(pieceShape)];
    }

    Vec2ui& BitsetManager::GetDimensionsOfPiece(PieceShape pieceShape) {
        return pieceShapeDimensions[PieceShapeToUInt(pieceShape)];
    }

    Vec2ui& BitsetManager::GetEdgeDimensionsOfPiece(PieceShape pieceShape) {
        return pieceEdgeCornerDimensions[PieceShapeToUInt(pieceShape)];
    }

    std::vector<std::bitset<484>> BitsetManager::PBMPieceDataToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize, const Vec2ui& offset) {
        std::vector<std::bitset<484>> bitsets = std::vector<std::bitset<484>>();
        unsigned int minX = 0;
        unsigned int minY = 0;
        unsigned int maxX = pieceSize;
        unsigned int maxY = pieceSize;

        for (unsigned int i = 0; i < 21; i++) {
            std::bitset<484> bitset = std::bitset<484>();
            for (unsigned int x = minX; x < maxX; x++) {
                for (unsigned int y = minY; y < maxY; y++) {
                    bitset[(x + offset.x) % pieceSize + ((y + offset.y) % pieceSize) * 22] = !bitmap.GetData()[x + y * bitmap.GetWidth()];
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

    std::vector<Vec2ui> BitsetManager::LoadPieceDataDimensionsFromFile(std::string path) {
        std::ifstream inputStream(path);
        if (!inputStream) {
            std::cout << "Unable to open txt file at: " << path << "\n";
            std::exit(1);
        }

        std::string line;
        std::getline(inputStream, line);
        inputStream.close();

        std::vector<Vec2ui> pieceDimensions = std::vector<Vec2ui>();
        for (int i = 0; i < 21; i++) {
            pieceDimensions.push_back(Vec2ui(line[i * 2] - 48, line[i * 2 + 1] - 48));
        }
        return pieceDimensions;
    }
}  // namespace HokusBlokus::Blokus