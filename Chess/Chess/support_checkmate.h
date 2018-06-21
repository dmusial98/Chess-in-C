#ifndef SUPPORT_CHECKMATE_H
#define SUPPORT_CHECKMATE_H

//funtions telling about checkmate

//checks checkmates for only one piece possible moves
Bool Is_it_chekmate_for_one_piece(Board_struct** Board, Pieces colour_of_piece, Pieces colour_of_King,
	Board_struct last_enemy_move, Player turn);

//checks checkmates for all pieces possible moves
Bool Is_it_checkmate_main_function(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_piece,
	Board_struct last_enemy_move, Player turn);

//function pilot a game in check case
Player checks_support(Bool *is_it_correct, Bool *possible_move, Bool *black_King_threatened, 
	Bool *white_King_threatened, int *oldX, int *oldY, int *x, int *y, Pieces *Which_one,
	Board_struct *last_move, Board_struct **Board, char* info, Pieces *What_was_there, Player *turn,
	Pieces colour_of_King);

//function checks does King is threatened
Player support_for_condition_from_check(Bool *black_King_threatened, Bool *is_it_correct, Bool *possible_move,
	Bool *white_King_threatened, int *oldX, int *oldY, int *x, int *y, Pieces *Which_one, Board_struct *last_move,
	Board_struct** Board, char* info, Pieces *What_was_there, Player *turn);

#endif