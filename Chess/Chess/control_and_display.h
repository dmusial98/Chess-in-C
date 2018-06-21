#include"structures_and_enums.h"

#ifndef CONTROL_AND_DISPLAY_H
#define CONTROL_AND_DISPLAY_H

/* controling pieces and displaying the chessboard */

//support for displaying pieces
void display_Piece(Board_struct** Board, int i, int j);

//displaying whole chessboard
void displayChessboard(Board_struct** Board, Player *turn, int x, int y, char* info);

//controlling the pieces 
void arrow_control(Board_struct** Board, Player *turn, int * x, int * y, char * str1);

#endif
