#include "pieceManager.hpp"

using namespace HokusBlokus::Util;

namespace HokusBlokus::Blokus {
	std::vector<Piece> PieceManager::pieces = std::vector<Piece>();

	void PieceManager::Init(const std::string& executionPath) {
		std::array<std::array<PieceBitmaskComplement, 8>, 21> complementsPerPiece = LoadBitmasks(std::filesystem::canonical(std::filesystem::path(executionPath).append("../generatedResources/")));

		for (unsigned int i = 0; i < 21; i++) {
			pieces.push_back(Piece(std::vector<PieceBitmaskComplement>(complementsPerPiece[i].begin(), complementsPerPiece[i].end())));
		}
		Logging::logger << "Piecemanager initialized\n";
	}

	Piece& PieceManager::GetPiece(PieceShape pieceShape) {
		return pieces[PieceShapeToInt(pieceShape)];
	}

	// PRIVATE

	std::array<std::array<PieceBitmaskComplement, 8>, 21> PieceManager::LoadBitmasks(const std::string& pathToResources) {
		std::array<std::array<PieceBitmaskComplement, 8>, 21> complementsPerPiece = std::array<std::array<PieceBitmaskComplement, 8>, 21>();

		Logging::logger << "Path to generated resources:" + pathToResources + "\n";
		if (!std::filesystem::exists(pathToResources)) {
			Logging::logger << "Path to generated resources does not exist. Were the resources generated?\n";
			exit(1);
		}

		for (int i = 0; i < 8; i++) {
			std::string pathToComplement = pathToResources + "/Complement_" + std::to_string(i) + "/";
			if (!std::filesystem::exists(pathToComplement)) {
				Logging::logger << "Path to complement" << i << " was not found. Were the resources generated?\n";
				exit(1);
			}

			std::array<std::array<PieceBitmask, 3>, 21> complementaryBitmasks = std::array<std::array<PieceBitmask, 3>, 21>();
			char orientation = ' ';
			bool flipped = false;

			for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(pathToComplement)) {
				if (entry.is_regular_file() && entry.path().extension() == ".pbm") {
					PBM::PBMImage complementBitmap = PBM::PBMLoader::LoadPBM(entry.path());

					std::string filename = entry.path().filename().string();
					std::string fileDescribtor = filename.substr(filename.find("_"));
					char type = 'S';

					// Orientation
					if (fileDescribtor.find("N") != std::string::npos) {
						orientation = 'N';
					} else if (fileDescribtor.find("E") != std::string::npos) {
						orientation = 'E';
					} else if (fileDescribtor.find("S") != std::string::npos) {
						orientation = 'S';
					} else if (fileDescribtor.find("W") != std::string::npos) {
						orientation = 'W';
					}

					// Type
					if (fileDescribtor.find("C") != std::string::npos) {
						type = 'C';
					} else if (fileDescribtor.find("B") != std::string::npos) {
						type = 'B';
					}

					// Flipped
					if (fileDescribtor.find("F") != std::string::npos) {
						flipped = true;
					}

					if (type == 'S') {
						std::array<std::bitset<484>, 21> temporaryBitmaps = PBMPieceDataToFullScaleBitsets(complementBitmap, 5, Vec2i(1, 1));
						for (int k = 0; k < 21; k++) {
							complementaryBitmasks[k][0] = PieceBitmask(temporaryBitmaps[k], MaskType::Shape);
						}
					}

					if (type == 'C') {
						std::array<std::bitset<484>, 21> temporaryBitmaps = PBMPieceDataToFullScaleBitsets(complementBitmap, 7, Vec2i(0, 0));
						for (int k = 0; k < 21; k++) {
							complementaryBitmasks[k][1] = PieceBitmask(temporaryBitmaps[k], MaskType::Corner);
						}
					}

					if (type == 'B') {
						std::array<std::bitset<484>, 21> temporaryBitmaps = PBMPieceDataToFullScaleBitsets(complementBitmap, 7, Vec2i(0, 0));
						for (int k = 0; k < 21; k++) {
							complementaryBitmasks[k][2] = PieceBitmask(temporaryBitmaps[k], MaskType::Edge);
						}
					}
				}
			}

			// Creating complements from loaded data
			for (int k = 0; k < 21; k++) {
				PieceRotation rotation = PieceRotation::NONE;
				if (orientation == 'N') {
					rotation = PieceRotation::NONE;
				} else if (orientation == 'E') {
					rotation = PieceRotation::RIGHT;
				} else if (orientation == 'S') {
					rotation = PieceRotation::MIRROR;
				} else if (orientation == 'W') {
					rotation = PieceRotation::LEFT;
				}

				complementsPerPiece[k][i] = PieceBitmaskComplement(complementaryBitmasks[k], rotation, flipped);
			}
		}
		return complementsPerPiece;
	}

	std::array<std::bitset<484>, 21> PieceManager::PBMPieceDataToFullScaleBitsets(const PBM::PBMImage& bitmap, unsigned int pieceSize, const Vec2i& offset) {
		std::array<std::bitset<484>, 21> bitsets = std::array<std::bitset<484>, 21>();
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
			bitsets[i] = bitset;

			minX = maxX % bitmap.GetWidth();
			maxX = minX + pieceSize;

			if (minX == 0) {
				minY = maxY;
				maxY += pieceSize;
			}
		}
		return bitsets;
	}
}  // namespace HokusBlokus::Blokus