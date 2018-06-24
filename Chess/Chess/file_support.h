#ifndef FILE_SUPPORT_H
#define FILE_SUPPORT_H

Bool save_to_file(char* name_of_file, char* info, Board_struct **Board, Player *turn, int *Which_function,
	Bool *white_King_threatened, Bool *black_King_threatened, Board_struct *last_move);
//saving actual state of game to file

Bool read_from_file(char* name_of_file, char* info, Board_struct **Board, Player* turn, int *Which_function,
	Bool *white_King_threatened, Bool *black_King_threatened, Board_struct *last_move);
//reading a game from file

#endif