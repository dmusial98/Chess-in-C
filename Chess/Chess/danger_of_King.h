#ifndef DANGER_OF_KING_H
#define DANGER_OF_KING_H

Bool which_piece_threaten(Board_struct **Board, Pieces colour_of_piece, int a, int b, int i, int j);

Bool Does_piece_threaten_King(Board_struct **Board, Pieces colour_of_piece, Pieces colour_of_King);

Bool Is_King_threatened(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_threating);

#endif