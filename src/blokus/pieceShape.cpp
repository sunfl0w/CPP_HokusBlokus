#include "pieceShape.hpp"

using namespace HokusBlokus::Util;

namespace HokusBlokus::Blokus {
    int PieceShapeToInt(PieceShape pieceShape) {
        return static_cast<int>(pieceShape);
    }

    std::string PieceShapeToString(PieceShape pieceShape) {
        if(pieceShape == PieceShape::MONOMINO) {
            return "MONO";
        } else if(pieceShape == PieceShape::DOMINO) {
            return "DOMINO";
        } else if(pieceShape == PieceShape::TRIO_L) {
            return "TRIO_L";
        } else if(pieceShape == PieceShape::TRIO_I) {
            return "TRIO_I";
        } else if(pieceShape == PieceShape::TETRO_I) {
            return "TETRO_I";
        } else if(pieceShape == PieceShape::TETRO_L) {
            return "TETRO_L";
        } else if(pieceShape == PieceShape::TETRO_O) {
            return "TETRO_O";
        } else if(pieceShape == PieceShape::TETRO_T) {
            return "TETRO_T";
        } else if(pieceShape == PieceShape::TETRO_Z) {
            return "TETRO_Z";
        } else if(pieceShape == PieceShape::PENTO_I) {
            return "PENTO_I";
        } else if(pieceShape == PieceShape::PENTO_U) {
            return "PENTO_U";
        } else if(pieceShape == PieceShape::PENTO_L) {
            return "PENTO_L";
        } else if(pieceShape == PieceShape::PENTO_V) {
            return "PENTO_V";
        } else if(pieceShape == PieceShape::PENTO_P) {
            return "PENTO_P";
        } else if(pieceShape == PieceShape::PENTO_W) {
            return "PENTO_W";
        } else if(pieceShape == PieceShape::PENTO_R) {
            return "PENTO_R";
        } else if(pieceShape == PieceShape::PENTO_X) {
            return "PENTO_X";
        } else if(pieceShape == PieceShape::PENTO_Z) {
            return "PENTO_Z";
        } else if(pieceShape == PieceShape::PENTO_Y) {
            return "PENTO_Y";
        } else if(pieceShape == PieceShape::PENTO_T) {
            return "PENTO_T";
        } else {
            return "PENTO_S";
        }
    }

    PieceShape IntToPieceShape(int value) {
        return static_cast<PieceShape>(value);
    }

    PieceShape StringToPieceShape(std::string pieceShapeString) {
        if(pieceShapeString == "MONO") {
            return PieceShape::MONOMINO;
        } else if(pieceShapeString == "DOMINO") {
            return PieceShape::DOMINO;
        } else if(pieceShapeString == "TRIO_L") {
            return PieceShape::TRIO_L;
        } else if(pieceShapeString == "TRIO_I") {
            return PieceShape::TRIO_I;
        } else if(pieceShapeString == "TETRO_I") {
            return PieceShape::TETRO_I;
        } else if(pieceShapeString == "TETRO_L") {
            return PieceShape::TETRO_L;
        } else if(pieceShapeString == "TETRO_O") {
            return PieceShape::TETRO_O;
        } else if(pieceShapeString == "TETRO_T") {
            return PieceShape::TETRO_T;
        } else if(pieceShapeString == "TETRO_Z") {
            return PieceShape::TETRO_Z;
        } else if(pieceShapeString == "PENTO_I") {
            return PieceShape::PENTO_I;
        } else if(pieceShapeString == "PENTO_U") {
            return PieceShape::PENTO_U;
        } else if(pieceShapeString == "PENTO_L") {
            return PieceShape::PENTO_L;
        } else if(pieceShapeString == "PENTO_V") {
            return PieceShape::PENTO_V;
        } else if(pieceShapeString == "PENTO_P") {
            return PieceShape::PENTO_P;
        } else if(pieceShapeString == "PENTO_W") {
            return PieceShape::PENTO_W;
        } else if(pieceShapeString == "PENTO_R") {
            return PieceShape::PENTO_R;
        } else if(pieceShapeString == "PENTO_X") {
            return PieceShape::PENTO_X;
        } else if(pieceShapeString == "PENTO_Z") {
            return PieceShape::PENTO_Z;
        } else if(pieceShapeString == "PENTO_Y") {
            return PieceShape::PENTO_Y;
        } else if(pieceShapeString == "PENTO_T") {
            return PieceShape::PENTO_T;
        } else if(pieceShapeString == "PENTO_S") {
            return PieceShape::PENTO_S;
        } else {
            Logger::getInstance() << "Unable to convert: " << pieceShapeString << " to a valid PieceShape.\n";
            exit(1);
        }
    }
}