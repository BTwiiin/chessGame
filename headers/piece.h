#pragma once
#include <iostream>

enum class PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    QUEEN,
    ROOK,
    KING,
    EMPTY
};


class Piece {
private:
    PieceType type;
    bool isWhite;
public:
    Piece(PieceType type, bool isWhite);
    PieceType getType() const { return type; }
    bool isWhite_() const { return isWhite; }
    //bool isMoveValid(int x1, int y1, int x2, int y2,const Piece* type) const ;
    //overloading of output operator<<
    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
    friend std::ostream& operator<<(std::ostream& os, const PieceType& pieceType);
};