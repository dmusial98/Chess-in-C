#include"structures_and_enums.h"
#include"danger_of_King.h"
#include"support_for_moves.h"

#include<stdlib.h>

Bool Does_Rook_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Rook) {	
	//return True when King is checked (threatened)
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Rook) {//finding Rook
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {//finding King
							if (a == i || b == j) {
								if (Main_funct_is_it_empty_Rook(Board, b, a, i, j)) return True;
							}
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Does_Bishop_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Bishop) {
	//return True when King is checked (threatened)
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Bishop) {//finding Bishop
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {//finding King
							if (abs(a - i) == abs(b - j)) {
								if (Main_funct_is_it_empty_Bishop(b, a, i, j, Board)) return True;
							}
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Does_Knight_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Knight) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Knight) { //finding Knight
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) { //finding King
							if (abs(a - i) == 2 && abs(b - j) == 1) return True;
							else if (abs(a - i) == 1 && abs(b - j) == 2) return True;
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Does_Queen_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Queen) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Queen) {//finding Queen
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {//finding King
							if (a == i || b == j) {
								if (Main_funct_is_it_empty_Rook(Board, b, a, i, j)) return True;
							}
							else if (abs(a - i) == abs(b - j)) {
								if (Main_funct_is_it_empty_Bishop(b, a, i, j, Board)) return True;
							}
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Does_Pawn_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Pawn) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Pawn) { //finding a Pawn
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) { //finding a King
							if (colour_of_Pawn == White_Pawn) {
								if (a - i == 1 && abs(b - j) == 1) {		//White Pawn threaten Black King
									return True;
								}
							}
							else if (colour_of_Pawn == Black_Pawn) {
								{ if (a - i == -1 && abs(b - j) == 1)		//Black Pawn threaten White King
									return True;
								}
							}
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Is_King_threatened(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_threating) {
	Pieces Rook, Knight, Bishop, Queen, Pawn;
	if (colour_of_threating > 0) {
		Rook = White_Rook, Knight = White_Knight, Bishop = White_Bishop,
			Queen = White_Queen, Pawn = White_Pawn;
	}
	else if (colour_of_threating < 0) {
		Rook = Black_Rook, Knight = Black_Knight, Bishop = Black_Bishop,
			Queen = Black_Queen, Pawn = Black_Pawn;
	}
		if (Does_Rook_threaten_King(Board, colour_of_King, Rook)) return True;
		else if (Does_Knight_threaten_King(Board, colour_of_King, Knight)) return True;
		else if (Does_Bishop_threaten_King(Board, colour_of_King, Bishop)) return True;
		else if (Does_Queen_threaten_King(Board, colour_of_King, Queen)) return True;
		else if (Does_Pawn_threaten_King(Board, colour_of_King, Pawn)) return True;
	return False;
}
