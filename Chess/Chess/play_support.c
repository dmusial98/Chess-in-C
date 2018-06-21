#include"structures_and_enums.h"
#include"support_checkmate.h"
#include"moves.h"
#include"danger_of_King.h"
#include"control_and_display.h"
#include "play_support.h"

#include<stdlib.h>

Bool Is_it_correct_move(Board_struct** Board, Pieces Which_one, int x, int y, int oldX, int oldY,
	Board_struct last_move, Player turn) {
	if (abs(Which_one) == White_King) return King_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square);
	else if (abs(Which_one) == White_Queen) return Queen_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board);
	else if (abs(Which_one) == White_Rook) return Rook_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board);
	else if (abs(Which_one) == White_Knight) return Knight_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square);
	else if (abs(Which_one) == White_Bishop) return Bishop_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board);
	else if (abs(Which_one) == White_Pawn) return Pawn_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board, Board[oldY][oldX].have_it_been_moved, last_move, turn);
	return False;
}

Bool Help_for_choosing_piece(Player turn, Pieces Which_one) {
	if (turn == White) {
		if (Which_one > 0) return True;
		else return False;
	}
	else {
		if (Which_one < 0) return True;
		else return False;
	}
}

Player playing(Player *turn, Board_struct** Board) {

	int x = 0, y = 0;
	int oldX, oldY;
	char* info = "Choose piece";
	Bool possible_move = True, is_it_correct = True, black_King_threatened = False, black_King_threatened2 = False;
	Bool white_King_threatened = False, white_King_threatened2 = False;   //various responsible for get knowing about choosen right target place for piece
																		  //various responsible for get knowing about choosen right colour of piece and target place
																		  // napisze potem
	Pieces Which_one, What_was_there;			//various required
	Board_struct last_move = Board[0][0];
	while (1) {
		do {	//warunek z podlozeniem sie na szacha
			do {		//warunek z wybraniem odpowiedniego miejsca wedlug podstawowych zasad poruszania sie
				do {		//warunek z wybraniem dobrej figury
					if (!is_it_correct || !possible_move) {
						if (!is_it_correct) info = "Please choose correct piece";
						else if (!possible_move) info = "You can't do that, please choose correct piece";
						Board[oldY][oldX].is_it_chosen = False;
					}
					else if (black_King_threatened || white_King_threatened) {  //informacja do podlozenia sie na szacha
						info = "You can't move in this place, your King would be checked";
						Board[y][x].Piece_on_square = What_was_there;
						Board[oldY][oldX].Piece_on_square = Which_one;	//przestawianie
						Board[oldY][oldX].is_it_chosen = False;
					}
					else info = "Choose piece";			//Chosing piece	
					possible_move = True;			//various responsible for get knowing about choosen right target place for piece
					arrow_control(Board, turn, &x, &y, info);
					Board[y][x].is_it_chosen = True;		//Taken a piece
					oldX = x;
					oldY = y;
					Which_one = Board[y][x].Piece_on_square;
					is_it_correct = Help_for_choosing_piece(*turn, Which_one); //checking does player choosed correct colour of piece
				} while (!is_it_correct);

				info = "Choose place for your piece";

				arrow_control(Board, turn, &x, &y, info);
				possible_move = Is_it_correct_move(Board, Which_one, x, y, oldX, oldY, last_move, *turn);
			} while (!possible_move);

			What_was_there = Board[y][x].Piece_on_square;
			Board[y][x].Piece_on_square = Which_one;
			Board[oldY][oldX].Piece_on_square = Empty;
			Board[oldY][oldX].is_it_chosen = False;			//przestawianie

			black_King_threatened = Is_King_threatened(Board, Black_King, White_Rook);
			white_King_threatened = Is_King_threatened(Board, White_King, Black_Rook);

		} while ((*turn == White && white_King_threatened == True) || (*turn == Black && black_King_threatened == True));
		//wystawienie sie na szacha

		if (support_for_condition_from_check(&black_King_threatened, &is_it_correct, &possible_move, &white_King_threatened, &oldX,
			&oldY, &x, &y, &Which_one, &last_move, Board, info, &What_was_there, turn) == Black) return Black;
		else if (support_for_condition_from_check(&black_King_threatened, &is_it_correct, &possible_move, &white_King_threatened, &oldX,
			&oldY, &x, &y, &Which_one, &last_move, Board, info, &What_was_there, turn) == White) return White;

		if (*turn == White) *turn = Black;
		else *turn = White;
		last_move = Board[y][x];


		if (abs(Which_one) == White_Pawn)
			Pawn_promotion(Board, y, x, turn, &x, &y);
		white_King_threatened = Is_King_threatened(Board, White_King, Black_Rook);
		black_King_threatened = Is_King_threatened(Board, Black_King, White_Rook);

		//szachowanie po promocji piona

		if (support_for_condition_from_check(&black_King_threatened, &is_it_correct, &possible_move, &white_King_threatened, &oldX,
			&oldY, &x, &y, &Which_one, &last_move, Board, info, &What_was_there, turn) == Black) return Black;
		else if (support_for_condition_from_check(&black_King_threatened, &is_it_correct, &possible_move, &white_King_threatened, &oldX,
			&oldY, &x, &y, &Which_one, &last_move, Board, info, &What_was_there, turn) == White) return White;
		//tutaj condition

	}
}
