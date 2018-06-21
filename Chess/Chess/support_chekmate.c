#include"structures_and_enums.h"
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

Bool Is_it_chekmate_for_one_piece(Board_struct** Board, Pieces colour_of_piece, Pieces colour_of_King, Board_struct last_enemy_move, Player turn) {

	Pieces makeshift_piece;
	Bool(*func_pointer)();
	if (abs(colour_of_piece) == White_Queen) func_pointer = &Queen_move;
	else if (abs(colour_of_piece) == White_Rook) func_pointer = &Rook_move;
	else if (abs(colour_of_piece) == White_Knight) func_pointer = &Knight_move;
	else if (abs(colour_of_piece) == White_Bishop) func_pointer = &Bishop_move;
	else if (abs(colour_of_piece) == White_Pawn) func_pointer = &Pawn_move;
	else  func_pointer = &King_move;
	//int cos2; ///na chwile tylko
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {//petla do znalezienia bierki
			if (Board[i][j].Piece_on_square == colour_of_piece) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if ((*func_pointer)(b, a, i, j, Board[a][b].Piece_on_square, Board[i][j].Piece_on_square, Board, Board[i][j].have_it_been_moved, last_enemy_move, turn)) {
							//ruch na dane pole jest mozliwe
							makeshift_piece = Board[a][b].Piece_on_square;
							Board[i][j].Piece_on_square = Empty;
							Board[a][b].Piece_on_square = colour_of_piece;		//przestawienie bierki

							if (!Is_King_threatened(Board, colour_of_King, negate(colour_of_piece))) {		//sprawdzenie czy szach dalej wystepuje

								Board[i][j].Piece_on_square = colour_of_piece;			//stwierdzono brak szacha dla danego ustawienia
								Board[a][b].Piece_on_square = makeshift_piece;		//ustawienie bierek na pierwotne pola
								return False;
							}
							Board[i][j].Piece_on_square = colour_of_piece;			//nie udalo sie zabezpieczyc przed szachem
							Board[a][b].Piece_on_square = makeshift_piece;			//ustawienie bierek na pierwotne pola
						}
					}
				}
			}
		}
	}
	return True;
}

Bool Is_it_checkmate_main_function(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_piece, Board_struct last_enemy_move, Player turn) {

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

Player checks_support(Bool *is_it_correct, Bool *possible_move, Bool *black_King_threatened, Bool *white_King_threatened, int *oldX, int *oldY, int *x, int *y, Pieces *Which_one,
	Board_struct *last_move, Board_struct **Board, char* info, Pieces *What_was_there, Player *turn, Pieces colour_of_King) {

	Bool King_threatened;
	if (colour_of_King == -1)
		King_threatened = *black_King_threatened;
	else King_threatened = *white_King_threatened;
	Bool King_threatened2 = False;

	do {	//gdy krol dalej szachowany
		do {	//warunek z prawidlowym ruchem z podstawowym poruszaniem sie bierek
			do {		// czy wybrano prawidlowy kolor bierki - bialy
				if (!is_it_correct || !possible_move || King_threatened2) {
					if (!is_it_correct) info = "Please choose correct piece";
					else if (!possible_move) info = "You can't do that, please choose correct piece";
					else if (King_threatened2) {
						info = "Black King is threatened, please do correct move";
						Board[*y][*x].Piece_on_square = *What_was_there;	//powrot do ustawienia sprzed ruchu - szacha
						Board[*oldY][*oldX].Piece_on_square = *Which_one;	//przestawianie
					}
					Board[*oldY][*oldX].is_it_chosen = False;
				}
				else if (King_threatened)
				{
					info = "Black King is checked";
					Board[*oldY][*oldX].is_it_chosen = False;
				}
				*possible_move = True;			//various responsible for get knowing about choosen right target place for piece

				if (Is_it_checkmate_main_function(Board, Black_King, Black_Rook, *last_move, *turn)) return White; // tu poprawa zwaracania!
																												   //miejsce na szacha

				arrow_control(Board, turn, x, y, info);
				Board[*y][*x].is_it_chosen = True;		//Taken a piece
				*oldX = *x;
				*oldY = *y;
				*Which_one = Board[*y][*x].Piece_on_square;
				*is_it_correct = Help_for_choosing_piece(*turn, *Which_one); //checking does player choosed correct colour of piece

			} while (!is_it_correct);

			info = "Choose place for your piece";
			arrow_control(Board, turn, x, y, info);
			*possible_move = Is_it_correct_move(Board, *Which_one, *x, *y, *oldX, *oldY, *last_move, *turn);
		} while (!possible_move);

		*What_was_there = Board[*y][*x].Piece_on_square;
		Board[*y][*x].Piece_on_square = *Which_one;
		Board[*oldY][*oldX].Piece_on_square = Empty;
		King_threatened2 = Is_King_threatened(Board, Black_King, White_Rook);
	} while (King_threatened2);
	if (*turn == White) *turn = Black;
	else *turn = White;
	*last_move = Board[*y][*x];
	Board[*oldY][*oldX].have_it_been_moved = True;
	*black_King_threatened = False;
	King_threatened2 = False;
	*white_King_threatened = False;
	return Nobody;
}

Player support_for_condition_from_check(Bool *black_King_threatened, Bool *is_it_correct, Bool *possible_move, Bool *white_King_threatened,
	int *oldX, int *oldY, int *x, int *y, Pieces *Which_one, Board_struct *last_move, Board_struct** Board, char* info, Pieces *What_was_there, Player *turn) {

	if (*black_King_threatened) { //szachowany czarny Król
		if (checks_support(is_it_correct, possible_move, black_King_threatened, white_King_threatened, oldX, oldY, x, y, Which_one, last_move,
			Board, info, What_was_there, turn, Black_King) == White) return White;
		else if (checks_support(is_it_correct, possible_move, black_King_threatened, white_King_threatened, oldX, oldY, x, y, Which_one, last_move,
			Board, info, What_was_there, turn, Black_King) == Black) return Black;
	}

	else if (*white_King_threatened) { //szachowany bialy krol
		if (checks_support(is_it_correct, possible_move, black_King_threatened, white_King_threatened, oldX, oldY, x, y, Which_one, last_move,
			Board, info, What_was_there, turn, White_King) == White) return White;
		else if (checks_support(is_it_correct, possible_move, black_King_threatened, white_King_threatened, oldX, oldY, x, y, Which_one, last_move,
			Board, info, What_was_there, turn, White_King) == Black) return Black;
	}
	return Nobody;
}
