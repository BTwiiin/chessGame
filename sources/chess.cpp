#include "../headers/chess.h"

Game::Game() {
    board = new Board();
    whoseMove = true;
}

Game::~Game() {
    delete board;
}


void Game::movePiece(std::string move) {
    //if (move == "exit") {
    //exit(0);
    //}
    if (move[0] < 65 || move[0] > 72 || move[3] < 65 || move[3] > 72) {
        std::cout << "Invalid move!" << std::endl;
        return;
    }
    if (move[1] < 49 || move[1] > 56 || move[4] < 49 || move[4] > 56) {
        std::cout << "Invalid move!" << std::endl;
        return;
    }

    int fromX = move[0] - 65;
    int fromY = 56 - move[1];
    if (board->isOccupiedByColor(fromX, fromY, getWhoseMove())) {
        int toX = move[3] - 65;
        int toY = 56 - move[4];
        bool flag = board->movePiece(fromX, fromY, toX, toY);
        if(flag)
            whoseMove = !whoseMove;
    }
    else {
        std::cout << "You can't move that piece!\n";
    }

}

void Game::drawBoard() const {
    board->drawBoard(getWhoseMove());
}