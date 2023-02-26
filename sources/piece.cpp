#include "../headers/piece.h"

Piece::Piece(PieceType type, bool isWhite) {
    this->type = type;
    this->isWhite = isWhite;
}

/*bool Piece::isMoveValid(int x1, int y1, int x2, int y2, const Piece* type) const {
	switch (type->getType()) {
	case PieceType::PAWN:
		if (type->isWhite_()) {
			if (x1 == x2 && (y1 - 1 == y2 || y1 - 2 == y2)) {
				return true;
			}
			else if (x1 + 1 == x2 && y1 - 1 == y2) {
				return true;
			}
			else if (x1 - 1 == x2 && y1 - 1 == y2) {
				return true;
			}
		}
		else {
			if (x1 == x2 && y1 + 1 == y2) {
				return true;
			}
			else if (x1 == x2 && y1 + 2 == y2) {
				return true;
			}
			else if (x1 + 1 == x2 && y1 + 1 == y2) {
				return true;
			}
			else if (x1 - 1 == x2 && y1 + 1 == y2) {
				return true;
			}
		}
	}
	std::cout << "Error: Invalid move" << std::endl;
	return false;
}*/

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    if (piece.isWhite) {
        os << "W";
    }
    else if (!piece.isWhite&& piece.type != PieceType::EMPTY){
        os << "B";
    }
    else {
        os << " ";
    }
    switch (piece.type) {
        case PieceType::PAWN:
            os << "P";
            break;
        case PieceType::KNIGHT:
            os << "N";
            break;
        case PieceType::BISHOP:
            os << "B";
            break;
        case PieceType::QUEEN:
            os << "Q";
            break;
        case PieceType::ROOK:
            os << "R";
            break;
        case PieceType::KING:
            os << "K";
            break;
        case PieceType::EMPTY:
            os << " ";
            break;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const PieceType& pieceType) {
    switch (pieceType) {
        case PieceType::PAWN:
            os << "P";
            break;
        case PieceType::KNIGHT:
            os << "N";
            break;
        case PieceType::BISHOP:
            os << "B";
            break;
        case PieceType::QUEEN:
            os << "Q";
            break;
        case PieceType::ROOK:
            os << "R";
            break;
        case PieceType::KING:
            os << "K";
            break;
    }
    return os;
}
