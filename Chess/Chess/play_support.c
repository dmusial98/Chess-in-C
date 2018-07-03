#include"structures_and_enums.h"
#include"definitions.h"
#include"support_checkmate.h"
#include"moves.h"
#include"danger_of_King.h"
#include"control_and_display.h"
#include "play_support.h"

#include<stdlib.h>

Bool Is_it_correct_move(Board_struct** Board, Pieces Which_one, int x, int y, int oldX, int oldY,
	Board_struct last_move, Player turn) { 
	if (abs(Which_one) == White_King) return King_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, 
		Board[oldY][oldX].Piece_on_square);
	else if (abs(Which_one) == White_Queen) return Queen_move(x, y, oldY, oldX, Board[y][x].Piece_on_square,
		Board[oldY][oldX].Piece_on_square, Board);
	else if (abs(Which_one) == White_Rook) return Rook_move(x, y, oldY, oldX, Board[y][x].Piece_on_square,
		Board[oldY][oldX].Piece_on_square, Board);
	else if (abs(Which_one) == White_Knight) return Knight_move(x, y, oldY, oldX, Board[y][x].Piece_on_square,
		Board[oldY][oldX].Piece_on_square);
	else if (abs(Which_one) == White_Bishop) return Bishop_move(x, y, oldY, oldX, Board[y][x].Piece_on_square,
		Board[oldY][oldX].Piece_on_square, Board);
	else if (abs(Which_one) == White_Pawn) return Pawn_move(x, y, oldY, oldX, Board[y][x].Piece_on_square, 
		Board[oldY][oldX].Piece_on_square, Board, Board[oldY][oldX].have_it_been_moved, last_move, turn);
	return False; 
}

Bool Help_for_choosing_piece(Player turn, Pieces Which_one) {
	if (turn == White) {
		if (Which_one > 0) return True;
		else return False;
	}
	else {
		if (Which_one < 0) return True;
		else return False;
	}
}

void return_from_conditions(Board_struct **Board, Bool *is_it_correct, Bool *possible_move, char **info, int *oldX,
	int *oldY, int *x, int *y, Pieces *What_was_there, Pieces *Which_one,
	Bool *black_King_threatened,Bool *white_King_threatened) {

	if (!*is_it_correct || !*possible_move) {
		if (!*is_it_correct) *info = "Please choose correct piece";
		else if (!*possible_move) *info = "You can't do that, please choose correct piece";
		Board[*oldY][*oldX].is_it_chosen = False;
	}
	else if (*black_King_threatened || *white_King_threatened) {  //when King move to threatened square
		*info = "You can't move in this place, your King would be checked";
		Board[*y][*x].Piece_on_square = *What_was_there;
		Board[*oldY][*oldX].Piece_on_square = *Which_one;	//setup pieces on before squares
		Board[*oldY][*oldX].is_it_chosen = False;
	}
	else *info = "Choose piece";			//Chosing piece	
}

//checking is this move correct
void correct_piece_condition(Board_struct **Board, Bool *possible_move, Bool *is_it_correct, Player *turn, int *x,
	int *y,int *oldX, int *oldY, Bool *white_King_threatened, Bool *black_King_threatened, int *Which_function, 
	char *info, Pieces *Which_one, Board_struct *last_move) {
	*possible_move = True;
	*Which_function = 0;
	arrow_control(Board, turn, x, y, info, Which_function, white_King_threatened, black_King_threatened, last_move);
	Board[*y][*x].is_it_chosen = True;		//Taken a piece
	*oldX = *x;
	*oldY = *y;
	*Which_one = Board[*y][*x].Piece_on_square;
	*is_it_correct = Help_for_choosing_piece(*turn, *Which_one); //checking does player choosed correct colour of piece
}

void checking_condition(Board_struct **Board, Pieces *What_was_there, Pieces *Which_one, Bool *black_King_threatened,
	Bool *white_King_threatened, int *x, int *y, int *oldX, int *oldY) {
	*What_was_there = Board[*y][*x].Piece_on_square;
	Board[*y][*x].Piece_on_square = *Which_one;
	Board[*oldY][*oldX].Piece_on_square = Empty;
	Board[*oldY][*oldX].is_it_chosen = False;			//making a move

	*black_King_threatened = Is_King_threatened(Board, Black_King, White_Rook);
	*white_King_threatened = Is_King_threatened(Board, White_King, Black_Rook);
	//checking dengers for King
}

Player checkmate_after_move(Board_struct **Board, Bool *possible_move, Bool *is_it_correct, Bool *black_King_threatened,
	Bool *white_King_threatened, Bool *Maybe_it_is_checkmate, int *x, int *y, int *oldX, int *oldY, int *Which_function,
	Pieces *Which_one, Pieces *What_was_there, Board_struct *last_move, char *info, Player *turn) {

	*Maybe_it_is_checkmate = support_for_condition_from_check(black_King_threatened, is_it_correct,
		possible_move, white_King_threatened, oldX, oldY, x, y, Which_one, last_move, Board, info,
		What_was_there, turn, Which_function, False);
	if (*Maybe_it_is_checkmate == True) {
		if (*white_King_threatened)return Black;
		else return White;
	}

	*Which_function = 0;

	if (abs(*Which_one) == White_Pawn)
		Pawn_promotion(Board, *y, *x, turn, x, y);
	*white_King_threatened = Is_King_threatened(Board, White_King, Black_Rook);
	*black_King_threatened = Is_King_threatened(Board, Black_King, White_Rook);

	//Checking (dangers) of King after pawn promotion

	*Maybe_it_is_checkmate = support_for_condition_from_check(black_King_threatened, is_it_correct,
		possible_move, white_King_threatened, oldX, oldY, x, y, Which_one, last_move, Board, info,
		What_was_there, turn, Which_function, False);
	if (*Maybe_it_is_checkmate == True) {
		if (*white_King_threatened)return Black;
		else return White;
	}
	*Which_function = 0;

	if (*turn == White) *turn = Black;
	else *turn = White;
	*last_move = Board[*y][*x];
	return Nobody;
}

Player playing(Player *turn, Board_struct** Board, int *Which_function) {

	int x = 0, y = 0; //variables for setting position of piece
	int oldX, oldY;	//variables saving old position of piece
	char* info = "Choose piece";
	Bool possible_move = True, is_it_correct = True;
	//possible_move variable responsible for get knowing about choosen right target place for piece
	//is_it_correct variable telling about choosing correct colour of piece
	Bool white_King_threatened = False, white_King_threatened2 = False;
	Bool black_King_threatened = False, black_King_threatened2 = False;
	//variables responsible for getting know about checks (dangers of King)
	Bool Maybe_it_is_checkmate;										
	*Which_function = 0;													 
	Pieces Which_one, What_was_there;			//Which_one telling about pieces which player chosen
	Board_struct last_move = Board[0][0];
	Player variable_after_move;
	while (1) {
		do {	
			do {		
				do {
					return_from_conditions(Board, &is_it_correct, &possible_move, &info, &oldX, &oldY, &x, &y,
						&What_was_there, &Which_one, &black_King_threatened, &white_King_threatened);
					
					correct_piece_condition(Board, &possible_move, &is_it_correct, turn, &x, &y, &oldX, &oldY,
						&white_King_threatened, &black_King_threatened, Which_function, info, &Which_one, &last_move);

				} while (!is_it_correct); 

				info = "Choose place for your piece";
				arrow_control(Board, turn, &x, &y, info, Which_function, &white_King_threatened, &black_King_threatened, &last_move);
				possible_move = Is_it_correct_move(Board, Which_one, x, y, oldX, oldY, last_move, *turn); 
			} while (!possible_move); //condition with choosing correct place for piece

			checking_condition(Board, &What_was_there, &Which_one, &black_King_threatened, &white_King_threatened,
				&x, &y, &oldX, &oldY);

		} while ((*turn == White && white_King_threatened == True) || (*turn == Black && black_King_threatened == True));
		//condition with making danger of King after own turn

		variable_after_move = checkmate_after_move(Board, &possible_move, &is_it_correct, &black_King_threatened,
			&white_King_threatened, &Maybe_it_is_checkmate, &x, &y, &oldX, &oldY, Which_function, &Which_one,
			&What_was_there, &last_move, info, turn);

		if (variable_after_move == White)
			return White;
		else if (variable_after_move == Black)
			return Black;
	}
}
