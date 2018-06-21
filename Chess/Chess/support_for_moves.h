#ifndef SUPPORT_FOR_MOVES_H
#define SUPPORT_FOR_MOVES_H

//funtion checks does piece capture piece the same colour
Bool first_condition_for_move(Pieces Is_it_empty, Pieces colour);


//function returning array with statistics for counting squares between two squares
int *diffrences_for_move(int *array_with_info_about_diffrences_for_move, int letter_move_to, int number_move_to,
	int number_move_from, int letter_move_from);
	
//supporting function checking is it empty between squares horizontally or upright
Bool Check_is_it_empty_between_squares_Rook(int orientation, int difference, int sign_of_difference,
	int number_move_from, int letter_move_from, Board_struct** Board);

//supporting function checking is it empty between squares crosswise
Bool Check_is_it_empty_between_squares_Bishop(int difference_horizontally, int sign_of_difference_horizontally,
	int sign_of_difference_upright, int number_move_from, int letter_move_from, Board_struct** Board);

//function checking is it empty between squares horizontally or upright
Bool Main_funct_is_it_empty_Rook(Board_struct** Board, int letter_move_to, int number_move_to, int number_move_from,
	int letter_move_from);

// function checking is it empty between squares crosswise
Bool Main_funct_is_it_empty_Bishop(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Board_struct** Board);

#endif