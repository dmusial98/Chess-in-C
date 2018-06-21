#ifndef STRUCTURES_AND_ENUMS_H
#define STRUCTURES_AND_ENUMS_H


typedef enum { False = 0, True = 1 } Bool; //wlasny typ bool
typedef enum { Black = -1, Nobody = 0, White = 1 } Player; //mowi czyja kolej
typedef enum {
	Empty = 0, White_King = 1, White_Queen = 2, White_Rook = 3, White_Bishop = 4, White_Knight = 5, White_Pawn = 6,
	Black_King = -1, Black_Queen = -2, Black_Rook = -3, Black_Bishop = -4, Black_Knight = -5, Black_Pawn = -6
} Pieces;
//wlasny typ dla bierek

typedef struct {
	Pieces Piece_on_square;
	char letter;
	char number;
	Bool have_it_been_moved;
	Bool is_it_chosen;
} Board_struct;

#endif