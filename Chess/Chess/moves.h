#ifndef MOVES_H
#define MOVES_H

//functions checking does this move is possible

Bool King_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from, Pieces Is_it_empty,
	Pieces colour);

Bool Rook_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct** Board);

Bool Knight_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour);

Bool Bishop_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct** Board);

Bool Queen_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct** Board);

Bool Pawn_move(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from,
	Pieces Is_it_empty, Pieces colour, Board_struct **Board, Bool Have_it_been_moved, Board_struct last_enemy_move,
	Player turn);

//function checks is it pawn promotion and commute Pawn for chosen piece
void Pawn_promotion(Board_struct** Board, int number_move_to, int letter_move_to, Player *turn, int *x, int *y);

#endif