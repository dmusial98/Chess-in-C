#ifndef CONTROL_AND_DISPLAY_H
#define CONTROL_AND_DISPLAY_H

/* controling pieces and displaying the chessboard */

//support for displaying pieces
void display_Piece(Board_struct** Board, int i, int j);

void display_top_of_row();

void display_middle_square(Board_struct** Board, int i, int j, int x, int y, Pieces colour_of_piece);

void display_instructions(Player *turn, char *info);

void displayChessboard(Board_struct **Board, Player *turn, int x, int y, char* info);

void new_cordinate_arrow(int *x, int *y, int * arrow);
	
void arrow_control(Board_struct **Board, Player *turn, int *x, int *y, char *str1, int *Which_function,
	Bool *white_King_threatened, Bool *black_King_threatened, Board_struct *last_move);
#endif
