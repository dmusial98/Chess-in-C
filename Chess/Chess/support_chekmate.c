#include"structures_and_enums.h"
#include"definitions.h"
#include"moves.h"
#include"support_checkmate.h"
#include"control_and_display.h"
#include"danger_of_King.h"
#include"play_support.h"

#include<stdlib.h>

int negate(int argument) {
	argument = argument - argument - argument;
	return argument;
}

Bool is_it_checkmate_after_move(Board_struct **Board, Pieces *makeshift_piece, Pieces colour_of_King, 
	Pieces colour_of_piece, int a, int b, int i, int j) {
	//move on this place is possible
	*makeshift_piece = Board[a][b].Piece_on_square;
	Board[i][j].Piece_on_square = Empty;
	Board[a][b].Piece_on_square = colour_of_piece;	//setup piece on possible move

	if (!Is_King_threatened(Board, colour_of_King, negate(colour_of_piece))) {
		//checking is it chekmate (end of game)

		Board[i][j].Piece_on_square = colour_of_piece;		//when it isn't checkmate
		Board[a][b].Piece_on_square = *makeshift_piece;		//setup piece on old square
		return False;
	}
	Board[i][j].Piece_on_square = colour_of_piece;			//we have check for this piece
	Board[a][b].Piece_on_square = *makeshift_piece;			//setup piece on old square
	return True;
}

Bool Is_it_chekmate_for_one_piece(Board_struct** Board, Pieces colour_of_piece, Pieces colour_of_King, 
	Board_struct last_enemy_move, Player turn) {

	Pieces makeshift_piece;
	Bool(*func_pointer)();
	if (abs(colour_of_piece) == White_Queen) func_pointer = &Queen_move;
	else if (abs(colour_of_piece) == White_Rook) func_pointer = &Rook_move;
	else if (abs(colour_of_piece) == White_Knight) func_pointer = &Knight_move;
	else if (abs(colour_of_piece) == White_Bishop) func_pointer = &Bishop_move;
	else if (abs(colour_of_piece) == White_Pawn) func_pointer = &Pawn_move;
	else  func_pointer = &King_move;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_piece) { //finding piece which threating King
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if ((*func_pointer)(b, a, i, j, Board[a][b].Piece_on_square, Board[i][j].Piece_on_square,
							Board, Board[i][j].have_it_been_moved, last_enemy_move, turn)) {
							if (!is_it_checkmate_after_move(Board, &makeshift_piece, colour_of_King, colour_of_piece,
							a, b, i, j)) return False; //move on this place is possible
						}
					}
				}
			}
		}
	}
	return True;
}

Bool Is_it_checkmate_main_function(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_piece,
	Board_struct last_enemy_move, Player turn) {
	//colour of King is the same like colour of colour_of_piece their moves would safe King for checkmate
	Pieces Queen, Rook, Bishop, Knight, Pawn, King = colour_of_King;
	if (colour_of_piece > 0) {
		Queen = White_Queen; Rook = White_Rook; Bishop = White_Bishop; Knight = White_Knight; Pawn = White_Pawn;
	}
	else if (colour_of_piece < 0) {
		Queen = Black_Queen, Rook = Black_Rook, Bishop = Black_Bishop, Knight = Black_Knight, Pawn = Black_Pawn;
	}

	if (!Is_it_chekmate_for_one_piece(Board, Queen, King, last_enemy_move, turn)) return False;
	if (!Is_it_chekmate_for_one_piece(Board, Rook, King, last_enemy_move, turn)) return False;
	if (!Is_it_chekmate_for_one_piece(Board, Bishop, King, last_enemy_move, turn)) return False;
	if (!Is_it_chekmate_for_one_piece(Board, Knight, King, last_enemy_move, turn)) return False;
	if (!Is_it_chekmate_for_one_piece(Board, Pawn, King, last_enemy_move, turn)) return False;
	if (!Is_it_chekmate_for_one_piece(Board, King, King, last_enemy_move, turn)) return False;

	return True;
}

Player checks_support(Bool *is_it_correct, Bool *possible_move, Bool *black_King_threatened,
	Bool *white_King_threatened, int *oldX, int *oldY, int *x, int *y, Pieces *Which_one, Board_struct *last_move,
	Board_struct **Board, char* info, Pieces *What_was_there, Player *turn, Pieces colour_of_King,
	int *Which_function, Bool start_from_file) {
	
	*Which_function = 1;  //Which_function can have two values 0 or 1 -> check state or not
	Pieces patronal_piece;
	Bool King_threatened;
	if (colour_of_King == Black_King) {
		King_threatened = *black_King_threatened;
		patronal_piece = Black_Bishop; //example of piece which can safe King (important only colour)
	}
	else { King_threatened = *white_King_threatened; 
	patronal_piece = White_Bishop; //example of piece which can safe King (important only colour)
	}
	Bool King_threatened2 = False;

	do {	//when King is in danger
		do {	//condition with choosing correct square for piece
			do {		//condition with correct choosing colour of piece
				if (!*is_it_correct || !*possible_move || King_threatened2) {
					if (!*is_it_correct) info = "Please choose correct piece";
					else if (!*possible_move) info = "You can't do that, please choose correct piece";
					else if (King_threatened2) {
						info = "Black King is threatened, please do correct move";
						Board[*y][*x].Piece_on_square = *What_was_there;	//setup piece on previous square
						Board[*oldY][*oldX].Piece_on_square = *Which_one;	
					}
					Board[*oldY][*oldX].is_it_chosen = False;
				}
				else if (King_threatened)
				{
					if (colour_of_King == White_King)
						info = "White King is checked";
				else if(colour_of_King == Black_King)
					info = "Black King is checked";
					
					Board[*oldY][*oldX].is_it_chosen = False;
					if (!start_from_file) {
						if (*turn == White) *turn = Black;
						else *turn = White;
					}							//changing turn if game was loaded from file
				}
				*possible_move = True;			//various responsible for get knowing about choosen right target place for piece

				if (Is_it_checkmate_main_function(Board, colour_of_King, patronal_piece, *last_move, *turn)) 
				{
				if(colour_of_King == Black)
					return White;
				else return Black;
				}		//returning value tell about winner

				arrow_control(Board, turn, x, y, info, Which_function, white_King_threatened,
					black_King_threatened, last_move);
				Board[*y][*x].is_it_chosen = True;		//Taken a piece
				*oldX = *x;
				*oldY = *y;
				*Which_one = Board[*y][*x].Piece_on_square;
				*is_it_correct = Help_for_choosing_piece(*turn, *Which_one); 
												//checking does player choosed correct colour of piece

			} while (!*is_it_correct);

			info = "Choose place for your piece";
			arrow_control(Board, turn, x, y, info, Which_function, white_King_threatened, 
				black_King_threatened, last_move);
			*possible_move = Is_it_correct_move(Board, *Which_one, *x, *y, *oldX, *oldY, *last_move, *turn);
		} while (!(*possible_move)); //information about choosing correct place for piece

		*What_was_there = Board[*y][*x].Piece_on_square;
		Board[*y][*x].Piece_on_square = *Which_one; //setup piece on chosen place
		Board[*oldY][*oldX].Piece_on_square = Empty;
		King_threatened2 = Is_King_threatened(Board, colour_of_King, negate(patronal_piece));
	} while (King_threatened2);  //condition with danger of King

	*last_move = Board[*y][*x]; 
	Board[*oldY][*oldX].have_it_been_moved = True;
	*black_King_threatened = False;
	King_threatened2 = False;
	*white_King_threatened = False;		
	return Nobody;
}

Player support_for_condition_from_check(Bool *black_King_threatened, Bool *is_it_correct, Bool *possible_move, Bool *white_King_threatened,
	int *oldX, int *oldY, int *x, int *y, Pieces *Which_one, Board_struct *last_move, Board_struct** Board, char* info, Pieces *What_was_there,
	Player *turn, int *Which_function, Bool start_from_file) {

	if (*black_King_threatened) { //black King is checked
		Player Maybe_it_is_chekmate = checks_support(is_it_correct, possible_move, black_King_threatened, white_King_threatened, oldX, oldY, x, y, Which_one, last_move,
			Board, info, What_was_there, turn, Black_King, Which_function, start_from_file);
		if (Maybe_it_is_chekmate == White) return White;
		else if (Maybe_it_is_chekmate == Black) return Black;
	} // returning colour of winner of the game

	else if (*white_King_threatened) { //white King i checked
		Player Maybe_it_is_chekmate = checks_support(is_it_correct, possible_move, black_King_threatened, white_King_threatened, oldX, oldY, x, y, Which_one, last_move,
			Board, info, What_was_there, turn, White_King, Which_function, start_from_file);
		if ( Maybe_it_is_chekmate == White) return White;
		else if(Maybe_it_is_chekmate == Black) return Black;
	} //returning colourof winner of the game
	return Nobody;
}
