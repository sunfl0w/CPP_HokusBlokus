#pragma once

#include "color.hpp"
#include "pieceShape.hpp"
#include "vec2i.hpp"
#include "moveType.hpp"
#include "pieceRotation.hpp"

namespace HokusBlokus::Blokus {
    /**
     * @brief Class representing a Move for the game Blokus
     * 
     */
    class Move {
    private:
        /**
         * @brief Move destination position. This is the upper left corner of the moved Piece
         * 
         */
        Vec2i destination; 

        /**
         * @brief The moved PieceShape
         * 
         */
        PieceShape pieceShape;

        /**
         * @brief Color of the moved PieceShape
         * 
         */
        Color color;

        /**
         * @brief Type of Move
         * 
         */
        MoveType moveType;

        /**
         * @brief Complement number of the move Piece. Used mostly internally
         * 
         */
        int complementNumber;

    public:
        /**
         * @brief Constructs a new empty Move
         * 
         */
        Move();
        
        /**
         * @brief Constructs a new Move
         * 
         * @param destination Destination
         * @param pieceShape Moved PieceShape
         * @param color Moved Color
         * @param moveType MoveType
         * @param complementNumber Complement number of moved PieceShape/Piece
         */
        Move(Vec2i destination, PieceShape pieceShape, Color color, MoveType moveType, int complementNumber);

        /**
         * @brief Equality operator
         * 
         * @param other Other Move
         * @return true When equal
         * @return false When not equal
         */
        bool operator==(const Move& other);

        /**
         * @brief Non-Equality operator
         * 
         * @param other Other Move
         * @return true When not equal
         * @return false When equal
         */
        bool operator!=(const Move& other);

        /**
         * @brief Gets the Destination of the Move
         * 
         * @return const Vec2i& 
         */
        const Vec2i& GetDestination() const;

        /**
         * @brief Gets the moved PieceShape
         * 
         * @return PieceShape 
         */
        PieceShape GetPieceShape() const;

        /**
         * @brief Gets the moved Color
         * 
         * @return Color 
         */
        Color GetColor() const;
        
        /**
         * @brief Gets the MoveType
         * 
         * @return MoveType 
         */
        MoveType GetMoveType() const;

        /**
         * @brief Gets the complement number of the moved PieceShape/Piece
         * 
         * @return int 
         */
        int GetComplementNumber() const;
    };
}  // namespace Blokus