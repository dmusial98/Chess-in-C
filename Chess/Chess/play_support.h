#ifndef PLAY_SUPPORT_H
#define PLAY_SUPPORT_H

//funtions responsible for piloting whole game  

//checks does this move is possible
Bool Is_it_correct_move(Board_struct** Board, Pieces Which_one, int x, int y, int oldX, int oldY,
	Board_struct last_move, Player turn); 

//checks does player chosed correct colour of piece
Bool Help_for_choosing_piece(Player turn, Pieces Which_one);

//piloting whole game
Player playing(Player *turn, Board_struct** Board, int *Which_function);

#endif
