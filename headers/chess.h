#pragma once
#include <iostream>
#include "boardr.h"

class Game {
private:
    Board* board;
    // this variable is used to determine whose move it is
    // true = white
    // false = black
    bool whoseMove;
public:
    Game();
    ~Game();
    // movePiece is used to translate the coordinates from a user for the function movePiece in class Board
    void movePiece(std::string move);
    void drawBoard() const;
    bool getWhoseMove() const { return whoseMove; }
    void start();
};