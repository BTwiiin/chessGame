#include "../headers/boardr.h"
#include <iostream>


Board::Board() {
    ////* Initialize the starting board *////
    board[0][0] = new Piece(PieceType::ROOK, false);
    board[1][0] = new Piece(PieceType::KNIGHT, false);
    board[2][0] = new Piece(PieceType::BISHOP, false);
    board[3][0] = new Piece(PieceType::QUEEN, false);
    board[4][0] = new Piece(PieceType::KING, false);
    board[5][0] = new Piece(PieceType::BISHOP, false);
    board[6][0] = new Piece(PieceType::KNIGHT, false);
    board[7][0] = new Piece(PieceType::ROOK, false);
    for (int x = 0; x < 8; x++) {
        board[x][1] = new Piece(PieceType::PAWN, false);
    }
    board[0][7] = new Piece(PieceType::ROOK, true);
    board[1][7] = new Piece(PieceType::KNIGHT, true);
    board[2][7] = new Piece(PieceType::BISHOP, true);
    board[3][7] = new Piece(PieceType::QUEEN, true);
    board[4][7] = new Piece(PieceType::KING, true);
    board[5][7] = new Piece(PieceType::BISHOP, true);
    board[6][7] = new Piece(PieceType::KNIGHT, true);
    board[7][7] = new Piece(PieceType::ROOK, true);
    for (int x = 0; x < 8; x++) {
        board[x][6] = new Piece(PieceType::PAWN, true);
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 2; y < 6; y++) {
            board[x][y] = new Piece(PieceType::EMPTY, false);
        }
    }
    // Set the initial positions of the kings
    kingPos[0] = new std::pair<int, int>(4, 7); //pointer to the white king
    kingPos[1] = new std::pair<int, int>(4, 0); //pointer to the black king
}

Board::Board(const Board& other) {
    // Copy over the pieces
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (other.board[x][y]->getType() == PieceType::EMPTY) {
                board[x][y] = new Piece(PieceType::EMPTY, false);
            }
            else {
                board[x][y] = new Piece(*(other.board[x][y]));
            }
        }
    }

    // Copy over the king positions
    kingPos[0] = new std::pair<int, int>(*(other.kingPos[0]));
    kingPos[1] = new std::pair<int, int>(*(other.kingPos[1]));
}

Board::~Board() {
    // delete all pieces
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            delete board[x][y];
        }
    }
}

// SETTERS
void Board::setKingPos(int x, int y, bool isWhite) {
    if (isWhite) {
        kingPos[0]->first = x;
        kingPos[0]->second = y;
    }
    else {
        kingPos[1]->first = x;
        kingPos[1]->second = y;
    }
}


//draws the board
void Board::drawBoard(const bool whoseMove) {
    if(whoseMove)
        std::cout << "White's move" << std::endl;
    else
        std::cout << "Black's move" << std::endl;

    std::cout << " |A |B |C |D |E |F |G |H |" << std::endl; // I changed a way of drawing the board
    for (int y = 0; y <= 7; y++) {
        std::cout << "-+--+--+--+--+--+--+--+--+-" << std::endl;
        std::cout << 8 - y << "|";
        for (int x = 0; x < 8; x++) {
            std::cout << *board[x][y];
            std::cout << "|";
        }
        std::cout << 8 - y << std::endl;
    }
    std::cout << "-+--+--+--+--+--+--+--+--+-" << std::endl;
    std::cout << " |A |B |C |D |E |F |G |H |" << std::endl;
    if(isCheck(whoseMove))
        std::cout << "CHECK!" << std::endl;
    else
        std::cout << "NOT CHECK" << std::endl;
}

bool Board::isMoveValidPawn(int x1, int y1, int x2, int y2) const {
    if (board[x1][y1]->isWhite_()) {
        if (y1 == 6) {
            if (y2 == 4 && x1 == x2 && isEmpty(x2, y2) && isEmpty(x2, y2 - 1)){
                return true;
            }
        }
        if (y2 == y1 - 1 && x1 == x2 && isEmpty(x2, y2)) {
            return true;
        }
        if (y2 == y1 - 1 && (x2 == x1 + 1 || x2 == x1 - 1) && isOccupiedByColor(x2, y2, false) && !isEmpty(x2, y2)) {
            return true;
        }
    }
    else {
        if (y1 == 1) {
            if (y2 == 3 && x1 == x2 && isEmpty(x2, y2)) {
                return true;
            }
        }
        if (y2 == y1 + 1 && x1 == x2 && isEmpty(x2, y2)) {
            return true;
        }
        if (y2 == y1 + 1 && (x2 == x1 + 1 || x2 == x1 - 1) && isOccupiedByColor(x2, y2, true)) {
            return true;
        }
    }
    //std::cout << "Invalid move!" << std::endl;
    return false;
}

bool Board::isMoveValidRook(int x1, int y1, int x2, int y2) const {
    if (x1 == x2) {
        if (y1 < y2) {
            for (int y = y1 + 1; y < y2; y++) {
                if (!isEmpty(x1, y)) {
                    //std::cout << "Invalid move!" << std::endl;
                    return false;
                }
            }
        }
        else {
            for (int y = y1 - 1; y > y2; y--) {
                if (!isEmpty(x1, y)) {
                    //std::cout << "Invalid move!" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }
    else if (y1 == y2) {
        if (x1 < x2) {
            for (int x = x1 + 1; x < x2; x++) {
                if (!isEmpty(x, y1)) {
                    //std::cout << "Invalid move!" << std::endl;
                    return false;
                }
            }
        }
        else {
            for (int x = x1 - 1; x > x2; x--) {
                if (!isEmpty(x, y1)) {
                    //std::cout << "Invalid move!" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }
    //std::cout << "Invalid move!" << std::endl;
    return false;
}

bool Board::isMoveValidKnight(int x1, int y1, int x2, int y2) const {
    if (x1 == x2 + 1 || x1 == x2 - 1) {
        if (y1 == y2 + 2 || y1 == y2 - 2) {
            return true;
        }
    }
    else if (x1 == x2 + 2 || x1 == x2 - 2) {
        if (y1 == y2 + 1 || y1 == y2 - 1) {
            return true;
        }
    }
    return false;
}

bool Board::isMoveValidBishop(int x1, int y1, int x2, int y2) const {
    // Check that the bishop is moving diagonally
    if (std::abs(x2 - x1) != std::abs(y2 - y1)) {
        return false;
    }
    // Check that there are no pieces blocking the bishop's path
    int x = (x2 - x1) > 0 ? 1 : -1;
    int y = (y2 - y1) > 0 ? 1 : -1;
    for (int i = 1; i < std::abs(x2 - x1); i++) {
        if (!isEmpty(x1 + i * x, y1 + i * y)) {
            return false;
        }
    }
    return true;

}

bool Board::isMoveValidKing(int x1, int y1, int x2, int y2) const {
    if (std::abs(x2 - x1) <= 1 && std::abs(y2 - y1)) {
        Board checkBoard(*this); // Create a copy of the board
        checkBoard.moveKingForCheck(x1, y1, x2, y2); // Move the king to the new position
        checkBoard.setKingPos(x2, y2, this->board[x1][y1]->isWhite_()); // Update the king's position
        if(checkBoard.isCheck(board[x1][y1]->isWhite_()))
            std::cout << "King is in check!" << std::endl;


        return !checkBoard.isCheck(board[x1][y1]->isWhite_());

    }
    return false;

}

bool Board::isMoveValid(int x1, int y1, int x2, int y2) const {
    if (board[x1][y1]->isWhite_() == board[x2][y2]->isWhite_() && board[x2][y2]->getType() != PieceType::EMPTY) {
        //std::cout << "Invalid move!" << std::endl;
        return false;
    }
    switch (board[x1][y1]->getType()) {
        case PieceType::PAWN:
            return isMoveValidPawn(x1, y1, x2, y2);
            break;
        case PieceType::ROOK:
            return isMoveValidRook(x1, y1, x2, y2);
            break;
        case PieceType::KNIGHT:
            return isMoveValidKnight(x1, y1, x2, y2);
            break;
        case PieceType::BISHOP:
            return isMoveValidBishop(x1, y1, x2, y2);
            break;
        case PieceType::QUEEN:
            return isMoveValidRook(x1, y1, x2, y2) || isMoveValidBishop(x1, y1, x2, y2); // Queen can move like a rook or a bishop
            break;
        case PieceType::KING:
            return isMoveValidKing(x1, y1, x2, y2);
            break;
    }
    return false;
}

bool Board::isCheck(const bool whoseMove) const {
    // Determine the position of the current player's king
    std::pair<int, int>* kingPosPtr = kingPos[whoseMove ? 0 : 1];
    int kingX = kingPosPtr->first;
    int kingY = kingPosPtr->second;

    // Iterate over all the opponent's pieces
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* piece = board[x][y];
            if (piece->isWhite_() != whoseMove) {  // if the piece belongs to the opponent
                if (isMoveValid(x, y, kingX, kingY)) {  // if the piece can attack the king
                    return true;
                }
            }
        }
    }
    return false;
}

//bool Board::isCheckForKing(const bool whoseMove) const {
//    // Determine the position of the current player's king
//    std::pair<int, int>* kingPosPtr = kingPos[whoseMove ? 0 : 1];
//    int kingX = kingPosPtr->first;
//    int kingY = kingPosPtr->second;
//
//    // Iterate over all the opponent's pieces
//    for (int x = 0; x < 8; x++) {
//        for (int y = 0; y < 8; y++) {
//            Piece* piece = board[x][y];
//            if (piece->isWhite_() != whoseMove) {  // if the piece belongs to the opponent
//                if (isMoveValid(x, y, kingX, kingY)) {  // if the piece can attack the king
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}

bool Board::movePiece(int x1, int y1, int x2, int y2) {
    if (isMoveValid(x1, y1, x2, y2)){
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = new Piece(PieceType::EMPTY, false);
        return true;
    }
    return false;
}

void Board::moveKingForCheck(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = new Piece(PieceType::EMPTY, false);
}

bool Board::isEmpty(int x, int y) const {
    return board[x][y]->getType() == PieceType::EMPTY;
}

bool Board::isOccupiedByColor(int x, int y, bool isWhite) const{
    return board[x][y]->isWhite_() == isWhite;
}

Piece& Board::getPiece(int x, int y) {
    // Check that the given coordinates are within the board
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        throw std::out_of_range("Coordinates out of range");
    }

    // Return a reference to the Piece at the given coordinates
    return *board[x][y];
}

Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }
    // Copy the board
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            *board[x][y] = *other.board[x][y];
        }
    }
    // Copy the king positions
    *kingPos[0] = *other.kingPos[0];
    *kingPos[1] = *other.kingPos[1];
    return *this;
}

