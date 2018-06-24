#ifndef DANGER_OF_KING_H
#define DANGER_OF_KING_H

// all funtions check does piece threaten King

Bool Does_Rook_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Rook);

Bool Does_Bishop_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Bishop);

Bool Does_Knight_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Knight);

Bool Does_Queen_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Queen);

Bool Does_Pawn_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Pawn);

Bool Is_King_threatened(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_threating);
//this function checks does any piece threaten King

#endif