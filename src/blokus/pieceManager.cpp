#include "pieceManager.hpp"

namespace HokusBlokus::Blokus {
    std::vector<Piece> PieceManager::pieces = std::vector<Piece>();

    void PieceManager::Init() {
        std::array<std::vector<PieceBitmask>, 21> pieceBitmasks = LoadBitmasks();

        for(unsigned int i = 0; i < 21; i++) {
            pieces.push_back(Piece(pieceBitmasks[i]));
        }
    }

    Piece& PieceManager::GetPiece(PieceShape pieceShape) {
        return pieces[PieceShapeToInt(pieceShape)];
    }

    //PRIVATE

    std::array<std::vector<PieceBitmask>, 21> PieceManager::LoadBitmasks() {
        std::string pathToResources = "generatedResources/";
        if (!std::filesystem::exists(pathToResources)) {
            std::cout << "Path to generated resources does not exist. Were the resources generated?\n";
            exit(1);
        }

        std::vector<PBM::PBMImage> pieceBitmaps = std::vector<PBM::PBMImage>();
        std::vector<MaskType> pieceBitmapMaskTypes = std::vector<MaskType>();

        for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(pathToResources)) {
            if (entry.is_regular_file() && entry.path().extension() == ".pbm") {
                pieceBitmaps.push_back(PBM::PBMLoader::LoadPBM(entry.path()));

                std::string filename = entry.path().filename().string();
                if(filename[16] == 'C' || filename[17] == 'C') {
                    pieceBitmapMaskTypes.push_back(MaskType::Corner);
                } else if(filename[16] == 'E' || filename[17] == 'E') {
                    pieceBitmapMaskTypes.push_back(MaskType::Edge);
                } else {
                    pieceBitmapMaskTypes.push_back(MaskType::Shape);
                }
            }
        }

        std::array<std::vector<PieceBitmask>, 21> pieceBitmasks = std::array<std::vector<PieceBitmask>, 21>();

        for(unsigned int i = 0; i < pieceBitmaps.size(); i++) {
            std::vector<std::bitset<484>> tempBitsets = std::vector<std::bitset<484>>();

            if (pieceBitmaps[i].GetWidth() == 25) {
                tempBitsets = PBMPieceDataToFullScaleBitsets(pieceBitmaps[i], 5, Vec2i(1, 1));
            } else {
                tempBitsets = PBMPieceDataToFullScaleBitsets(pieceBitmaps[i], 7, Vec2i(0, 0));
            }

            for (unsigned int k = 0; k < 21; k++) {
                pieceBitmasks[k].push_back(PieceBitmask(tempBitsets[k], pieceBitmapMaskTypes[i]));
            }
        }

        return pieceBitmasks;
    }

    std::vector<Vec2i> PieceManager::LoadPieceDimensions() {
        return LoadPieceDataDimensionsFromFile("resources/BlokusPieceShapeDimensions.txt");
    }

    std::vector<std::bitset<484>> PieceManager::PBMPieceDataToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize, const Vec2i& offset) {
        std::vector<std::bitset<484>> bitsets = std::vector<std::bitset<484>>();
        unsigned int minX = 0;
        unsigned int minY = 0;
        unsigned int maxX = pieceSize;
        unsigned int maxY = pieceSize;

        for (unsigned int i = 0; i < 21; i++) {
            std::bitset<484> bitset = std::bitset<484>();
            for (unsigned int x = minX; x < maxX; x++) {
                for (unsigned int y = minY; y < maxY; y++) {
                    bitset[(x % pieceSize) + offset.x + ((y % pieceSize) + offset.y) * 22] = !bitmap.GetData()[x + y * bitmap.GetWidth()];
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

    std::vector<Vec2i> PieceManager::LoadPieceDataDimensionsFromFile(std::string path) {
        std::ifstream inputStream(path);
        if (!inputStream) {
            std::cout << "Unable to open txt file with piece dimensions at: " << path << "\n";
            std::exit(1);
        }

        std::string line;
        std::getline(inputStream, line);
        inputStream.close();

        std::vector<Vec2i> pieceDimensions = std::vector<Vec2i>();
        for (int i = 0; i < 21; i++) {
            pieceDimensions.push_back(Vec2i(line[i * 2] - 48, line[i * 2 + 1] - 48));
        }
        return pieceDimensions;
    }
}  // namespace HokusBlokus::Blokus