#include"structures_and_enums.h"
#include"definitions.h"
#include"making_chessboard.h"

#include<stdlib.h>

Board_struct** Fill_Board(Board_struct** Board) { //filing chessboard pieces for starting values
	Board[0][0].Piece_on_square = White_Rook; Board[0][7].Piece_on_square = White_Rook;
	Board[0][1].Piece_on_square = White_Knight; Board[0][6].Piece_on_square = White_Knight;
	Board[0][2].Piece_on_square = White_Bishop; Board[0][5].Piece_on_square = White_Bishop;
	Board[0][3].Piece_on_square = White_Queen; Board[0][4].Piece_on_square = White_King;
	for (int i = 0; i < 8; i++) Board[1][i].Piece_on_square = White_Pawn;
	Board[7][0].Piece_on_square = Black_Rook; Board[7][7].Piece_on_square = Black_Rook;
	Board[7][1].Piece_on_square = Black_Knight; Board[7][6].Piece_on_square = Black_Knight;
	Board[7][2].Piece_on_square = Black_Bishop; Board[7][5].Piece_on_square = Black_Bishop;
	Board[7][3].Piece_on_square = Black_Queen; Board[7][4].Piece_on_square = Black_King;
	for (int i = 0; i < 8; i++) Board[6][i].Piece_on_square = Black_Pawn;
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) Board[i][j].Piece_on_square = Empty;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i > 1 && i < 6)
				Board[i][j].have_it_been_moved = True;
			else Board[i][j].have_it_been_moved = False;
		}
	}
	return Board;
}

Board_struct** Make_Board() {		//making chessboard in dynamic structure
	Board_struct ** Board = calloc(8, sizeof(Pieces*));
	for (int i = 0; i < 8; i++) Board[i] = calloc(8, sizeof(Board_struct));

	char filling_number = '1';
	char filling_letter = 'a';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Board[i][j].number = filling_number;
		} filling_number++;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Board[j][i].letter = filling_letter;
			Board[j][i].is_it_chosen = False;
		} filling_letter++;
	}
	return Board;
}
