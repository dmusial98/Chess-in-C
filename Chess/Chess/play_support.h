#ifndef PLAY_SUPPORT_H
#define PLAY_SUPPORT_H

//funtions responsible for piloting whole game  

//checks does this move is possible
Bool Is_it_correct_move(Board_struct** Board, Pieces Which_one, int x, int y, int oldX, int oldY,
	Board_struct last_move, Player turn);

//checks does player chosed correct colour of piece
Bool Help_for_choosing_piece(Player turn, Pieces Which_one);

//communicate new messages on console
void return_from_conditions(Board_struct **Board, Bool *is_it_correct, Bool *possible_move, char **info, int *oldX,
	int *oldY, int *x, int *y, Pieces *What_was_there, Pieces *Which_one,
	Bool *black_King_threatened, Bool *white_King_threatened);

//checking is this move correct
void correct_piece_condition(Board_struct **Board, Bool *possible_move, Bool *is_it_correct, Player *turn, int *x,
	int *y, int *oldX, int *oldY, Bool *white_King_threatened, Bool *black_King_threatened, int *Which_function,
	char *info, Pieces *Which_one, Board_struct *last_move);

//checking condition with threatening piece
void checking_condition(Board_struct **Board, Pieces *What_was_there, Pieces *Which_one, Bool *black_King_threatened,
	Bool *white_King_threatened, int *x, int *y, int *oldX, int *oldY);

//checking is it checkmate after move
Player checkmate_after_move(Board_struct **Board, Bool *possible_move, Bool *is_it_correct, Bool *black_King_threatened,
	Bool *white_King_threatened, Bool *Maybe_it_is_checkmate, int *x, int *y, int *oldX, int *oldY, int *Which_function, Pieces *Which_one, Pieces *What_was_there,
	Board_struct *last_move, char *info, Player *turn);

//piloting whole game
Player playing(Player *turn, Board_struct** Board, int *Which_function);

#endif
