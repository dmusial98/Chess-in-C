#include"structures_and_enums.h"
#include"support_for_moves.h"

#include<stdlib.h>

Bool first_condition_for_move(Pieces Is_it_empty, Pieces colour) {
	//checking is piece on square have different colour than moving piece
		if (colour < 0) {
			if (Is_it_empty < 0) return False;
		}
		if (colour > 0) {
			if (Is_it_empty > 0) return False;	
	}
	return True;
}

int *diffrences_for_move(int *array_with_info_about_diffrences_for_move, int letter_move_to, int number_move_to,
	int number_move_from, int letter_move_from) {
	array_with_info_about_diffrences_for_move[0] = letter_move_to - letter_move_from; //sign of difference horizontally
	array_with_info_about_diffrences_for_move[1] = number_move_to - number_move_from; //sign_of_difference_upright
	array_with_info_about_diffrences_for_move[2] = abs(letter_move_to - letter_move_from); //difference horizontally
	array_with_info_about_diffrences_for_move[3] = abs(number_move_to - number_move_from);  //difference upright
	return array_with_info_about_diffrences_for_move;
}

Bool Check_is_it_empty_between_squares_Rook(int orientation, int difference, int sign_of_difference,
	int number_move_from, int letter_move_from, Board_struct** Board) {
	if (difference) {
		difference--;
		switch (orientation) {
			//orientation 0 -> horizontally, 1 -> upright
		case 0:
			for (int i = 1; i <= difference; i++) {
				if (sign_of_difference > 0) {
					if (Board[number_move_from][letter_move_from + i].Piece_on_square != Empty) return False;
				}
				else if (sign_of_difference < 0) {
					if (Board[number_move_from][letter_move_from - i].Piece_on_square != Empty) return False;
				}
			} break;
		case 1:
			for (int i = 1; i <= difference; i++) {
				if (sign_of_difference > 0) {
					if (Board[number_move_from + i][letter_move_from].Piece_on_square != Empty) return False;
				}
				else if (sign_of_difference < 0) {
					if (Board[number_move_from - i][letter_move_from].Piece_on_square != Empty) return False;
				}
			}
		}
	} return True;
}

Bool Check_is_it_empty_between_squares_Bishop(int difference_horizontally, int sign_of_difference_horizontally,
	int sign_of_difference_upright, int number_move_from, int letter_move_from, Board_struct** Board) {
	if (difference_horizontally) {
		difference_horizontally--;
		for (int i = 1; i <= difference_horizontally; i++) {
			if (sign_of_difference_horizontally > 0 && sign_of_difference_upright > 0) {
				if (Board[number_move_from + i][letter_move_from + i].Piece_on_square != Empty) return False;
			}
			else if (sign_of_difference_horizontally < 0 && sign_of_difference_upright > 0) {
				if (Board[number_move_from + i][letter_move_from - i].Piece_on_square != Empty) return False;
			}
			else if (sign_of_difference_horizontally > 0 && sign_of_difference_upright < 0) {
				if (Board[number_move_from - i][letter_move_from + i].Piece_on_square != Empty) return False;
			}
			else if (sign_of_difference_horizontally < 0 && sign_of_difference_upright < 0) {
				if (Board[number_move_from - i][letter_move_from - i].Piece_on_square != Empty) return False;
			}
		}
	}
	return True;
}

Bool Main_funct_is_it_empty_Rook(Board_struct** Board, int letter_move_to, int number_move_to, int number_move_from,
	int letter_move_from) { // returning true if all squares between starting and target square -> Rook's move type
	int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
	//sign of difference horizontally -> 0
	//sign_of_difference_upright      -> 1
	//difference horizontally         -> 2
	//difference upright              -> 3
	array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move,
		letter_move_to, number_move_to, number_move_from, letter_move_from);
	if (!Check_is_it_empty_between_squares_Rook(0, array_with_info_about_diffrences_for_move[2],
		array_with_info_about_diffrences_for_move[0], number_move_from, letter_move_from, Board))
	{
		free(array_with_info_about_diffrences_for_move);
		return False;
	}
	if (!Check_is_it_empty_between_squares_Rook(1, array_with_info_about_diffrences_for_move[3],
		array_with_info_about_diffrences_for_move[1], number_move_from, letter_move_from, Board))
	{
		free(array_with_info_about_diffrences_for_move);
		return False;
	}
	free(array_with_info_about_diffrences_for_move);
	return True;
}

Bool Main_funct_is_it_empty_Bishop(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Board_struct** Board) { // returning true if all squares between starting and target square -> Bishop's move type
	int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
	//sign of difference horizontally -> 0
	//sign_of_difference_upright      -> 1
	//difference horizontally         -> 2
	//difference upright              -> 3
	array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
	if (!Check_is_it_empty_between_squares_Bishop(array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], array_with_info_about_diffrences_for_move[1], (int)number_move_from, (int)letter_move_from, Board))
	{
		free(array_with_info_about_diffrences_for_move);
		return False;
	}
	return True;
}

