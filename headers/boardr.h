#pragma once
#include "piece.h"

class Board {
private:
    // 2D array of pieces
    Piece* board[8][8];
    // Pointers to the kings for checking check => [0] == white, [1] == black
    std::pair<int, int>* kingPos[2];
public:
    Board();
    Board(const Board& other);
    ~Board();

    void drawBoard(const bool whoseMove);
    // Returns the piece at the given position
    //Piece* getPiece(int x, int y);

    // Set of functions to check if a move is valid
    bool isMoveValid(int x1, int y1, int x2, int y2) const ;
    bool isMoveValidPawn(int x1, int y1, int x2, int y2) const ;
    bool isMoveValidRook(int x1, int y1, int x2, int y2) const ;
    bool isMoveValidKnight(int x1, int y1, int x2, int y2) const;
    bool isMoveValidBishop(int x1, int y1, int x2, int y2) const;
    bool isMoveValidKing(int x1, int y1, int x2, int y2) const;

    bool isCheck(const bool whoseMove) const;

    // Moves the piece at the given position to the given position
    bool movePiece(int x1, int y1, int x2, int y2);

    // Returns true if the given position is empty
    bool isEmpty(int x, int y) const;

    // Returns true if the given position is on the board
    bool isOnBoard(int x, int y);

    // Returns true if the given position is occupied by a piece of the given color
    bool isOccupiedByColor(int x, int y, bool isWhite) const ;

    // Returns true if the given position is occupied by a piece of the given type
    bool isOccupiedByType(int x, int y, PieceType type);

    //
    Piece& getPiece(int x, int y) const;

    // Operators
    Board& operator=(const Board& other);

};