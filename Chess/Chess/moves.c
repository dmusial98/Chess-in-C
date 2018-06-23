#include"structures_and_enums.h"
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
			return False;
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
		if (letter_move_from == letter_move_to && number_move_from == number_move_to) return False;  //checking does Queen stay in the same place?
		int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
		array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
		if (!Check_is_it_empty_between_squares_Rook(0, array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], number_move_from, letter_move_from, Board))
		{
			free(array_with_info_about_diffrences_for_move);
			return False;
		}
		if (!Check_is_it_empty_between_squares_Rook(1, array_with_info_about_diffrences_for_move[3], array_with_info_about_diffrences_for_move[1], number_move_from, letter_move_from, Board))
		{
			free(array_with_info_about_diffrences_for_move);
			return False;
		}

	}
	else if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) { //Bishop's move type

		int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
		//sign of difference horizontally -> 0
		//sign_of_difference_upright      -> 1
		//difference horizontally         -> 2
		//difference upright              -> 3
		array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
		if (!Check_is_it_empty_between_squares_Bishop(array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], array_with_info_about_diffrences_for_move[1], number_move_from, letter_move_from, Board))
		{
			free(array_with_info_about_diffrences_for_move);
			return False;
		}
	}
	else return False;
	return True;
}

Bool Pawn_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct **Board, Bool Have_it_been_moved, Board_struct last_enemy_move, Player turn) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;
	if (colour > 0) { //bialy pion

		if ((number_move_to - number_move_from) == 1 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //ruch bialym pionem o jedno pole do przodu
		else if ((number_move_to - number_move_from) == 1 && abs(letter_move_from - letter_move_to) == 1 && Is_it_empty < 0) return True; //zbicie w skosie przeciwnika
		else if ((number_move_to - number_move_from) == 2 && letter_move_to == letter_move_from && Is_it_empty == Empty && !Have_it_been_moved) {
			if (!Main_funct_is_it_empty_Rook(Board, letter_move_to, number_move_to, number_move_to, letter_move_to)) return False;
			return True;
		}  //pierwszy ruch piona bialego
		else if (number_move_to == 5 && number_move_from == 4 && last_enemy_move.number - 49 == 4 && last_enemy_move.Piece_on_square == Black_Pawn && abs(letter_move_to - letter_move_from) == 1) {
			Board[4][letter_move_to].Piece_on_square = Empty;
			return True;  //bicie w przelocie
		}
	}
	else if (colour < 0) { //czarny pion
		if ((number_move_to - number_move_from) == -1 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //ruch czarnym pionem o jedno pole do przodu
		else if ((number_move_to - number_move_from) == -1 && abs(letter_move_from - letter_move_to) == 1 && Is_it_empty > 0) return True; //zbicie w skosie przeciwnika
		else if ((number_move_to - number_move_from) == -2 && letter_move_to == letter_move_from && Is_it_empty == Empty && !Have_it_been_moved) {
			if (!Main_funct_is_it_empty_Rook(Board, letter_move_to, number_move_to, number_move_to, letter_move_to)) return False;
			return True;  //pierwszy ruch piona czarnego 
		}
		else if (number_move_to == 2 && number_move_from == 3 && last_enemy_move.number - 49 == 3 && last_enemy_move.Piece_on_square == White_Pawn && abs(letter_move_to - letter_move_from) == 1) {
			Board[3][letter_move_to].Piece_on_square = Empty;
			return True;  //bicie w przelocie  --- tutaj brakuje mi jeszcze ze przeciwnik ruszyl sie pionem o dwa pola do przodu 
		}
	}
	return False;
}

void Pawn_promotion(Board_struct** Board, int number_move_to, int letter_move_to, Player *turn, int *x, int *y) {
	if (number_move_to == 0) {
		displayChessboard(Board, turn, *x, *y, "For what do you want exchange pawn?\n");
		char buf[2];
		scanf("%s", buf);
		if (buf[0] == 'q') Board[number_move_to][letter_move_to].Piece_on_square = Black_Queen;
		else if (buf[0] == 'k') Board[number_move_to][letter_move_to].Piece_on_square = Black_Knight;
		else if (buf[0] == 'r') Board[number_move_to][letter_move_to].Piece_on_square = Black_Rook;
		else if (buf[0] == 'b') Board[number_move_to][letter_move_to].Piece_on_square = Black_Bishop;
	}
	else if (number_move_to == 7) {
		displayChessboard(Board, turn, *x, *y, "For what do you want exchange pawn?\n");
		char buf[2];
		scanf("%s", buf);
		if (buf[0] == 'q') Board[number_move_to][letter_move_to].Piece_on_square = White_Queen;
		else if (buf[0] == 'k') Board[number_move_to][letter_move_to].Piece_on_square = White_Knight;
		else if (buf[0] == 'r') Board[number_move_to][letter_move_to].Piece_on_square = White_Rook;
		else if (buf[0] == 'b') Board[number_move_to][letter_move_to].Piece_on_square = White_Bishop;
	}
}
