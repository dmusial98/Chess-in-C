#include "structures_and_enums.h"
#include "making_chessboard.h"
#include "control_and_display.h"
#include "play_support.h"
#include"danger_of_King.h"
#include"definitions.h"
#include"moves.h"
#include"support_checkmate.h"
#include"support_for_moves.h"

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

int main() {
	
		Board_struct** Board = Make_Board();  //making a chessboard for playing 
		Player turn = White;
		Player who_won = playing(&turn, Board);
		if (who_won == White) displayChessboard(Board, &turn, 0, 0, "White pieces won\n\n");
		else displayChessboard(Board, &turn, 0, 0, "Black pieces won\n\n");

	return 0;
}
