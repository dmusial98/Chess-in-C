#include"structures_and_enums.h"
#include"definitions.h"
#include"support_for_moves.h"
#include"control_and_display.h"
#include"moves.h"

#include <stdlib.h>
#include<stdio.h>

Bool King_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from, Pieces Is_it_empty,
	Pieces colour) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (abs(letter_move_to - letter_move_from) < 2 && abs(number_move_to - number_move_from) < 2) {
		if (number_move_to == number_move_from && letter_move_to == letter_move_from) return False;
	} 
	else return False;
	return True;
}

Bool Rook_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct** Board) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (letter_move_to == letter_move_from || number_move_to == number_move_from)
	{
		if (!Main_funct_is_it_empty_Rook(Board, letter_move_to, number_move_to, number_move_from, letter_move_from))
			return False; //chceking are empty squares between square starting and target place for Rook
		else return True;
	}
	return False;
}

Bool Knight_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (abs(number_move_to - number_move_from) == 2 && abs(letter_move_to - letter_move_from) == 1) return True;
	else if (abs(number_move_to - number_move_from) == 1 && abs(letter_move_to - letter_move_from) == 2) return True;
	return False;
}

Bool Bishop_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct** Board) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) && (number_move_to != number_move_from && letter_move_to != letter_move_from))
	{
		if (!Main_funct_is_it_empty_Bishop(letter_move_to, number_move_to, number_move_from, letter_move_from, Board))
			return False;
		else return True;
	}
	else return False;
}

Bool Queen_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct** Board) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (letter_move_to == letter_move_from || number_move_to == number_move_from) { //Rook's move type
		if (letter_move_from == letter_move_to && number_move_from == number_move_to) return False; 
		//checking does Queen stay in the same place?
		if (!Main_funct_is_it_empty_Rook(Board, letter_move_to, number_move_to, number_move_from, letter_move_from))
			return False; //chceking are empty squares between square starting and target place for Rook
		else return True;
	}
	else if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) 
		&& (number_move_to != number_move_from && letter_move_to != letter_move_from)) { //Bishop's move type

		if (!Main_funct_is_it_empty_Bishop(letter_move_to, number_move_to, number_move_from, letter_move_from, Board))
			return False;
		else return True;
	}
	else return False;
	return True;
}

Bool Pawn_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct **Board, Bool Have_it_been_moved, Board_struct last_enemy_move,
	Player turn) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;
	if (colour > 0) { //white Pawn

		if ((number_move_to - number_move_from) == 1 && letter_move_to == letter_move_from && Is_it_empty == Empty)
			return True;  //move white Pawn one square forward
		else if ((number_move_to - number_move_from) == 1 && abs(letter_move_from - letter_move_to) == 1 
			&& Is_it_empty < 0) return True; //capture obliquely
		else if ((number_move_to - number_move_from) == 2 && letter_move_to == letter_move_from && Is_it_empty == Empty
			&& !Have_it_been_moved) {
			if (!Main_funct_is_it_empty_Rook(Board, letter_move_to, number_move_to, number_move_to, letter_move_to))
				return False;

			return True;
		}  //First move of white Pawn
		else if (number_move_to == 5 && number_move_from == 4 && last_enemy_move.number - 49 == 4 &&
			last_enemy_move.Piece_on_square == Black_Pawn && abs(letter_move_to - letter_move_from) == 1) {
			Board[4][letter_move_to].Piece_on_square = Empty;
			return True;  //En passant
		}
	}
	else if (colour < 0) { //black Pawn
		if ((number_move_to - number_move_from) == -1 && letter_move_to == letter_move_from && Is_it_empty == Empty)
			return True;  //move black Pawn one square forward
		else if ((number_move_to - number_move_from) == -1 && abs(letter_move_from - letter_move_to) == 1 &&
			Is_it_empty > 0) return True; //capture obliquely
		else if ((number_move_to - number_move_from) == -2 && letter_move_to == letter_move_from && Is_it_empty == Empty && !Have_it_been_moved) {
			if (!Main_funct_is_it_empty_Rook(Board, letter_move_to, number_move_to, number_move_to, letter_move_to)) return False;
			return True;  //first move of black Pawn
		}
		else if (number_move_to == 2 && number_move_from == 3 && last_enemy_move.number - 49 == 3 && last_enemy_move.Piece_on_square == White_Pawn && abs(letter_move_to - letter_move_from) == 1) {
			Board[3][letter_move_to].Piece_on_square = Empty;
			return True;  //En passant 
		}
	}
	return False;
}

void Pawn_promotion(Board_struct** Board, int number_move_to, int letter_move_to, Player *turn, int *x, int *y) {
	if (number_move_to == 0) {
		displayChessboard(Board, turn, *x, *y, "For what do you want exchange pawn?\n");
		char buf = getchar();
		while (buf == 'q' || buf == 'r' || buf == 'k' || buf == 'b') {
			buf = getchar();
		}
		//changing Pawn for different piece
		if (buf == 'q') Board[number_move_to][letter_move_to].Piece_on_square = Black_Queen;
		else if (buf == 'k') Board[number_move_to][letter_move_to].Piece_on_square = Black_Knight;
		else if (buf == 'r') Board[number_move_to][letter_move_to].Piece_on_square = Black_Rook;
		else if (buf == 'b') Board[number_move_to][letter_move_to].Piece_on_square = Black_Bishop;
	} 
	else if (number_move_to == 7) {
		displayChessboard(Board, turn, *x, *y, 
			"For what do you want exchange pawn?\n q - Queen, r - Rook, k - Knight, b -Bishop");
		char buf = getchar();
		while (buf == 'q' || buf == 'r' || buf == 'k' || buf == 'b') {
			buf = getchar();
		}
		//changing Pawn for different piece
		if (buf == 'q') Board[number_move_to][letter_move_to].Piece_on_square = White_Queen;
		else if (buf == 'k') Board[number_move_to][letter_move_to].Piece_on_square = White_Knight;
		else if (buf == 'r') Board[number_move_to][letter_move_to].Piece_on_square = White_Rook;
		else if (buf == 'b') Board[number_move_to][letter_move_to].Piece_on_square = White_Bishop;
	}
}
