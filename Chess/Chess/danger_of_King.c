#include"structures_and_enums.h"
#include"definitions.h"
#include"danger_of_King.h"
#include"support_for_moves.h"

#include<stdlib.h>

Bool which_piece_threaten(Board_struct **Board, Pieces colour_of_piece, int a, int b, int i, int j) {
	if (abs(colour_of_piece) == White_Rook) {			//Rook threatens King
		if (a == i || b == j) {
			if (Main_funct_is_it_empty_Rook(Board, b, a, i, j)) return True;
			else return False;
		}
		else return False;
	}
	else if (abs(colour_of_piece) == White_Bishop) {	//Bishop threatens King
		if (abs(a - i) == abs(b - j)) {
			if (Main_funct_is_it_empty_Bishop(b, a, i, j, Board)) return True;
			else return False;
		}
		else return False;
	}
	else if (abs(colour_of_piece) == White_Knight) {	//Knight threatens King
		if (abs(a - i) == 2 && abs(b - j) == 1) return True;
		else if (abs(a - i) == 1 && abs(b - j) == 2) return True;
		else return False;
	}
	else if (abs(colour_of_piece) == White_Queen) {		//Queen threatens King
		if (a == i || b == j) {		//Rook's type move
			if (Main_funct_is_it_empty_Rook(Board, b, a, i, j)) return True;
			else return False;
		}
		else if (abs(a - i) == abs(b - j)) { //Bishop's type move
			if (Main_funct_is_it_empty_Bishop(b, a, i, j, Board)) return True;
			else return False;
		}
		else return False;
	}
	else if (abs(colour_of_piece) == White_Pawn) {
		if (colour_of_piece == White_Pawn) {
			if (a - i == 1 && abs(b - j) == 1) 		//White Pawn threaten Black King
				return True;
			else return False;
		}
		else if (colour_of_piece == Black_Pawn) {
			if (a - i == -1 && abs(b - j) == 1)		//Black Pawn threaten White King
				return True;
			else return False;
		}
	} else return False;
}

Bool Does_piece_threaten_King(Board_struct **Board, Pieces colour_of_piece, Pieces colour_of_King) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_piece) {//finding piece
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {//finding King
							if (which_piece_threaten(Board, colour_of_piece, a, b, i, j))
								return True;
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

	if(Does_piece_threaten_King(Board, Rook, colour_of_King)) return True;
	if (Does_piece_threaten_King(Board, Bishop, colour_of_King)) return True;
	if (Does_piece_threaten_King(Board, Knight, colour_of_King)) return True;
	if (Does_piece_threaten_King(Board, Queen, colour_of_King)) return True;
	if (Does_piece_threaten_King(Board, Pawn, colour_of_King)) return True;
	
	return False;
}
