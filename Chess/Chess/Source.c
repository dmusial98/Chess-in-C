#include <stdio.h>
#include <stdlib.h>
#include "rlutil.h"
#include <time.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define UP_BORDER 0
#define DOWN_BORDER 7
#define LEFT_BORDER 0
#define RIGHT_BORDER 7

typedef enum {Black = -1, White = 1} Player;
typedef enum {False = 0, True = 1} Bool; //wlasny typ bool
typedef enum {
	Empty = 0, White_King = 1, White_Queen = 2, White_Rook = 3, White_Bishop = 4, White_Knight = 5, White_Pawn = 6,
	Black_King = -1, Black_Queen = -2, Black_Rook = -3, Black_Bishop = -4, Black_Knight = -5, Black_Pawn = -6} Pieces; 
//wlasny typ dla bierek

typedef struct {
	Pieces Piece_on_square;
	char letter;
	char number;
	Bool have_it_been_moved;
	Bool is_it_chosen;
} Board_struct;

void timer(int sekundy) {		//funkcja odczekujaca zadany czas w sekundach
	int czas = 1000 * sekundy; // w milisekundach
	clock_t poczatek = clock();
	while (clock() < poczatek + czas);
}

Board_struct** Fill_Board(Board_struct** Board) { //wypelnianie szachownicy pionkami dla wartosci poczatkowych
	Board[0][0].Piece_on_square = White_Rook; Board[0][7].Piece_on_square = White_Rook;
	Board[0][1].Piece_on_square = White_Knight; Board[0][6].Piece_on_square = White_Knight;
	Board[0][2].Piece_on_square = White_Bishop; Board[0][5].Piece_on_square = White_Bishop;
	Board[0][3].Piece_on_square = White_Queen; Board[0][4].Piece_on_square = White_King;
	for (int i = 0; i < 8; i++) Board[1][i].Piece_on_square = White_Pawn;
	Board[7][0].Piece_on_square = Black_Rook; Board[7][7].Piece_on_square = Black_Rook;
	Board[7][1].Piece_on_square = Black_Knight; Board[7][6].Piece_on_square = Black_Knight;
	Board[7][2].Piece_on_square = Black_Bishop; Board[7][5].Piece_on_square = Black_Bishop;
	Board[7][3].Piece_on_square = Black_Queen; Board[7][4].Piece_on_square = Black_King;
	for (int i = 0; i < 8; i++) Board[6][i].Piece_on_square = Black_Pawn;
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) Board[i][j].Piece_on_square = Empty;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			Board[i][j].have_it_been_moved = False;
		}
	}
	for (int i = 6; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Board[i][j].have_it_been_moved = False;
		}
	}
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			Board[i][j].have_it_been_moved = True;
		}
	}
	return Board;
}

Board_struct** Make_Board() {		//tworzenie szachownicy w strukturze dynamicznej
	Board_struct ** Board = calloc(8, sizeof(Pieces*));
	for (int i = 0; i < 8; i++) Board[i] = calloc(8, sizeof(Board_struct));
	
	char filling_number = '1';
	char filling_letter = 'a';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Board[i][j].number = filling_number;
		} filling_number++;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Board[j][i].letter = filling_letter;
			Board[j][i].is_it_chosen = False;
		} filling_letter++;
	}
	Board =  Fill_Board(Board); //wypelnienie tablicy 
	return Board;
}

Bool first_condition_for_move(Pieces Is_it_empty, Pieces colour) {
	
	if (colour < 0) {
		if (Is_it_empty < 0) return False;
	}
	if (colour > 0) {
		if (Is_it_empty > 0) return False;		//sprawdzenie czy bierka nie zbija bierki swojego koloru
	}
	return True;
}

Bool King_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (abs(letter_move_to - letter_move_from) < 2 && abs(number_move_to - number_move_from) < 2) {
		if (number_move_to == number_move_from && letter_move_to == letter_move_from) return False;
	}
	else return False;
			return True;
	}

int *diffrences_for_move(int *array_with_info_about_diffrences_for_move, char letter_move_to, char number_move_to, char number_move_from, char letter_move_from){
	array_with_info_about_diffrences_for_move[0] = letter_move_to - letter_move_from; //sign of difference horizontally
	array_with_info_about_diffrences_for_move[1] = number_move_to - number_move_from; //sign_of_difference_upright
	array_with_info_about_diffrences_for_move[2] = abs(letter_move_to - letter_move_from); //difference horizontally
	array_with_info_about_diffrences_for_move[3] = abs(number_move_to - number_move_from);  //difference upright
	return array_with_info_about_diffrences_for_move;
}

Bool Check_is_it_empty_between_squares_Rook(int orientation, int difference, int sign_of_difference, int number_move_from, int letter_move_from, Board_struct** Board) {
	if (difference) {
		difference--;
		switch (orientation) {

		case 0:
			for (int i = 1; i <= difference; i++) {
				if (sign_of_difference > 0) {
					if (Board[number_move_from][letter_move_from + i].Piece_on_square != Empty) return False;
				}
				else if (sign_of_difference < 0) {
					if (Board[number_move_from][letter_move_from - i].Piece_on_square != Empty) return False;
				}
			} break;
		case 1:
			for (int i = 1; i <= difference; i++) {
				if (sign_of_difference > 0) {
					if (Board[number_move_from + i][letter_move_from].Piece_on_square != Empty) return False;
				}
				else if (sign_of_difference < 0) {
					if (Board[number_move_from - i][letter_move_from].Piece_on_square != Empty) return False;
				}
			}
		} 
	} return True;
}

Bool Check_is_it_empty_between_squares_Bishop (int difference_horizontally, int sign_of_difference_horizontally, int sign_of_difference_upright, int number_move_from, int letter_move_from, Board_struct** Board) {
	if (difference_horizontally) {
	difference_horizontally--;
	for (int i = 1; i <= difference_horizontally; i++) {
	if (sign_of_difference_horizontally > 0 && sign_of_difference_upright > 0) {
	if (Board[number_move_from + i][letter_move_from + i].Piece_on_square != Empty) return False;
	}
	else if (sign_of_difference_horizontally < 0 && sign_of_difference_upright > 0) {
	if (Board[number_move_from + i][letter_move_from - i].Piece_on_square != Empty) return False;
	}
	else if (sign_of_difference_horizontally > 0 && sign_of_difference_upright < 0) {
	if (Board[number_move_from - i][letter_move_from + i].Piece_on_square != Empty) return False;
	}
	else if (sign_of_difference_horizontally < 0 && sign_of_difference_upright < 0) {
	if (Board[number_move_from - i][letter_move_from - i].Piece_on_square != Empty) return False;
	}
	}
	}
	return True;
}

Bool Main_funct_is_it_empty_Rook(Board_struct** Board, int letter_move_to, int number_move_to, int number_move_from, int letter_move_from) { //wartosci pomniejszone dla tablicy
	int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
	//sign of difference horizontally -> 0
	//sign_of_difference_upright      -> 1
	//difference horizontally         -> 2
	//difference upright              -> 3
	array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
	if (!Check_is_it_empty_between_squares_Rook(0, array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], number_move_from, letter_move_from, Board))
	{
		free(array_with_info_about_diffrences_for_move);
		return False;
	}
	if (!Check_is_it_empty_between_squares_Rook(1, array_with_info_about_diffrences_for_move[3], array_with_info_about_diffrences_for_move[1], number_move_from, letter_move_from, Board))
	{
		free(array_with_info_about_diffrences_for_move);
		return False;
	}
	free(array_with_info_about_diffrences_for_move);
	return True;
}

Bool Main_funct_is_it_empty_Bishop(int letter_move_to, int number_move_to, int number_move_from, int letter_move_from, Board_struct** Board) {
	int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
	//sign of difference horizontally -> 0
	//sign_of_difference_upright      -> 1
	//difference horizontally         -> 2
	//difference upright              -> 3
	array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
	if (!Check_is_it_empty_between_squares_Bishop(array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], array_with_info_about_diffrences_for_move[1], (int)number_move_from, (int)letter_move_from, Board))
	{
		free(array_with_info_about_diffrences_for_move);
		return False;
	}
	return True;
}

Bool Rook_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour, Board_struct** Board) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (letter_move_to == letter_move_from || number_move_to == number_move_from) 
	{
		if(!Main_funct_is_it_empty_Rook(Board, (int)letter_move_to - 97, (int)number_move_to - 49, (int)number_move_from - 49, (int)letter_move_from - 97)) 
			return False;
	} 
	return True;
}

Bool Knight_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (abs(number_move_to - number_move_from) == 2 && abs(letter_move_to - letter_move_from) == 1) return True;
	else if (abs(number_move_to - number_move_from) == 1 && abs(letter_move_to - letter_move_from) == 2) return True;
	return False;
}

Bool Bishop_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour, Board_struct** Board) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) {
		if (!Main_funct_is_it_empty_Bishop((int)letter_move_to - 97, (int)number_move_to - 49, (int)number_move_from - 49, (int)letter_move_from - 97, Board))
			return False;
	}
	else return False;
	return True;
}

Bool Queen_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour, Board_struct** Board) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (letter_move_to == letter_move_from || number_move_to == number_move_from) { //Rook's move type
		if (letter_move_from == letter_move_to && number_move_from == number_move_to) return False;
		int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
		array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
		if (!Check_is_it_empty_between_squares_Rook(0, array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], (int)number_move_from - 49, (int)letter_move_from - 97, Board))
		{
			free(array_with_info_about_diffrences_for_move);
			return False;
		}
		if (!Check_is_it_empty_between_squares_Rook(1, array_with_info_about_diffrences_for_move[3], array_with_info_about_diffrences_for_move[1], (int)number_move_from - 49, (int)letter_move_from - 97, Board))
		{
			free(array_with_info_about_diffrences_for_move);
			return False;
		}
		
	} else if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) { //Bishop's move type
	
		int *array_with_info_about_diffrences_for_move = calloc(4, sizeof(int));
		//sign of difference horizontally -> 0
		//sign_of_difference_upright      -> 1
		//difference horizontally         -> 2
		//difference upright              -> 3
		array_with_info_about_diffrences_for_move = diffrences_for_move(array_with_info_about_diffrences_for_move, letter_move_to, number_move_to, number_move_from, letter_move_from);
		if (!Check_is_it_empty_between_squares_Bishop(array_with_info_about_diffrences_for_move[2], array_with_info_about_diffrences_for_move[0], array_with_info_about_diffrences_for_move[1], (int)number_move_from - 49, (int)letter_move_from - 97, Board))
		{
			free(array_with_info_about_diffrences_for_move);
			return False;
		}
	}
	else return False;
	return True;
}

Bool Pawn_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour, Bool Have_it_been_moved, Board_struct last_enemy_move) {

	if (!first_condition_for_move(Is_it_empty, colour)) return False;

	if (colour > 0) { //bialy pion
		
		if ((number_move_to - number_move_from) == 1 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //ruch bialym pionem o jedno pole do przodu
		else if ((number_move_to - number_move_from) == 1 && abs(letter_move_from - letter_move_to) == 1 && Is_it_empty < 0) return True; //zbicie w skosie przeciwnika
		else if (number_move_to == 6 && number_move_from == 5 && last_enemy_move.number == 5 && last_enemy_move.Piece_on_square == Black_Pawn && abs(letter_move_to - letter_move_from) == 1)
			return True;  //bicie w przelocie
		else if (!Have_it_been_moved) {
			if ((number_move_to - number_move_from) == 2 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //pierwszy ruch piona bialego
		}
	}

	if (colour < 0) { //czarny pion
		
		if ((number_move_to - number_move_from) == -1 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //ruch czarnym pionem o jedno pole do przodu
		else if ((number_move_to - number_move_from) == -1 && abs(letter_move_from - letter_move_to) == 1 && Is_it_empty > 0) return True; //zbicie w skosie przeciwnika
		else if (number_move_to == 3 && number_move_from == 4 && last_enemy_move.number == 4 && last_enemy_move.Piece_on_square == White_Pawn && abs(letter_move_to - letter_move_from) == 1)
			return True;  //bicie w przelocie
		else if (!Have_it_been_moved) {
			if ((number_move_to - number_move_from) == -2 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //pierwszy ruch piona czarnego
		}
	}
	return False;
	}

Bool Does_Rook_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Rook) {		//zwraca True gdy krol jest szachowany
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (Board[i][j].Piece_on_square == colour_of_Rook) {
					for (int a = 0; a < 8; a++) {
						for (int b = 0; b < 8; b++) {
							if (Board[a][b].Piece_on_square == colour_of_King) {
								if (a == i || b == j) {
									if (Main_funct_is_it_empty_Rook(Board, b, a, i, j)) return True;
								}
							}
						}
					}
				}
			}
		}
	return False;
}

Bool Does_Bishop_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Bishop) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Bishop) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {
							if (abs(a - i) == abs(b - j)) {
								if (Main_funct_is_it_empty_Bishop(Board, b, a, i, j)) return True;
							}
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Does_Knight_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Knight) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Knight) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {
							if (abs(a - i) == 2 && abs(b - j) == 1) return True;
							else if (abs(a - i) == 1 && abs(b - j) == 2) return True;
						}
					}
				}
			}
		}
	}
	return False;
}

Bool Does_Queen_threaten_King(Board_struct** Board, Pieces colour_of_King, Pieces colour_of_Queen) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].Piece_on_square == colour_of_Queen) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (Board[a][b].Piece_on_square == colour_of_King) {
							if (a == i || b == j) {
								if (Main_funct_is_it_empty_Rook(Board, b, a, i, j)) return True;
							}
							else if (abs(a - i) == abs(b - j)) {
								if (Main_funct_is_it_empty_Bishop(Board, b, a, i, j)) return True;
							}
						}
					}
				}
			}
		}
	} return False;
}

void display_Piece(Board_struct** Board, int i, int j){
		if (abs(Board[i][j].Piece_on_square) == 1)
			printf(" K");
		else if (abs(Board[i][j].Piece_on_square) == 2)
			printf(" Q");
		else if (abs(Board[i][j].Piece_on_square) == 3)
			printf(" R");
		else if (abs(Board[i][j].Piece_on_square) == 4)
			printf(" B");
		else if (abs(Board[i][j].Piece_on_square) == 5)
			printf("KN");
		else if (abs(Board[i][j].Piece_on_square) == 6)
			printf(" P");
	setColor(WHITE);
}

void displayChessboard(Board_struct** Board, Player turn, int x, int y, char* info)
{
	system("cls");
	setColor(WHITE);
	printf("\n   ");
	for (int p = 0; p < 8; p++) {
		printf("%c    ", 65 + p);		// letters on the top
	}
	printf("\n");
	for (int i = 7; i >= 0 ; i--) { // all 8 rows
		printf(" ");
		for (int j = 0; j < 8; j++) {	// TOP of every row
			printf("%c", 195);	printf("%c", 196); printf("%c", 196); printf("%c", 196); printf("%c", 180);
		}
		printf("\n");
		printf("%d", i+1);	// number on the left
		for (int j = 0; j < 8; j++) { // middle
			printf("%c", 124);			// left barrier

			if (Board[i][j].Piece_on_square > 0)			// PLAYER 1
			{ 
				if (Board[i][j].is_it_chosen == True) {
					setColor(LIGHTCYAN);
					display_Piece(Board, i, j);
				}
				else {
					if (i == y && j == x)  setColor(LIGHTCYAN);
					else setColor(YELLOW);	// YELLOW color
					display_Piece(Board, i, j);
				}
			}
			else if (Board[i][j].Piece_on_square < 0)	// PLAYER 2
			{
				if (Board[i][j].is_it_chosen == True) {
					setColor(LIGHTRED);
					display_Piece(Board, i, j);
				}
				else {
					if (i == y && j == x) setColor(LIGHTRED);
					else setColor(RED);	// RED color
					display_Piece(Board, i, j);
				}
			}
			else if(i == y && j == x)
				printf(" %c", 176);	
			else printf("  ");

			printf(" %c", 124);
		} 	printf("%d\n", i + 1);	// number on the right 
	}
	// BOTTOM of chessboard
	printf(" ");
	for (int i = 0; i < 8; i++) {
		printf("%c", 195); printf("%c", 196);	printf("%c", 196); printf("%c", 196);	 printf("%c", 180);
	}
	printf("\n   ");
	for (int p = 0; p < 8; p++) {
		printf("%c    ", 65 + p);		// letters on the bottom
	}
	printf("\n");
	if (turn == 1)	printf("\n\nWhite's turn\n\n");
	else printf("\n\nBlack's turn\n\n");
	printf("%s\n\n", info);
	printf("K - King, Q - Queen, R - Rook, B - Bishop, KN - Knight, P - Pawn\n");
	printf("Red -> BLACK, Yellow - WHITE");

}

void ArrowControl(Board_struct** Board, Player turn, int * x, int * y, char * str1)
{
	int arrow;
	int end;
	for (;;)
	{
		displayChessboard(Board, turn, *x, *y, str1);
		// printf statistics
		end = getch();
		if (end == 13) // PRESS to ENTER
		{
			return;
		}
		arrow = getch();

		if (arrow == DOWN_ARROW) {
			if (*y == UP_BORDER)
				*y = DOWN_BORDER;   // move to down border
			else
				*y = *y - 1;		// move up
		}
		if (arrow == LEFT_ARROW) {
			if (*x == LEFT_BORDER)
				*x = RIGHT_BORDER;   // move to right border
			else
				*x = *x - 1;		// move left
		}
		if (arrow == RIGHT_ARROW) {
			if (*x == RIGHT_BORDER)
				*x = LEFT_BORDER;   // move to left border
			else
				*x = *x + 1;		// move right
		}
		if (arrow == UP_ARROW) {
			if (*y == DOWN_BORDER)
				*y = UP_BORDER;   // move to up border
			else
				*y = *y + 1;		// move down
		}
	}
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
	
void playing(Player turn, Board_struct** Board) {
	
	int x = 0;
	int y = 0;
	int oldX;
	int oldY;
	char* info;
	Bool is_it_right_move;
	Bool is_it_correct = True;
	Pieces Which_one;
	Board_struct last_move = Board[0][0];
	while (1) {
		do {
			do {
				if (!is_it_correct) {
					if (!is_it_right_move)
						info = "You can't do that, please choose correct piece";
					else info = "Please choose correct piece";
					Board[oldY][oldX].is_it_chosen = False;
				}
				else info = "Choose piece";
				ArrowControl(Board, turn, &x, &y, info);
				Board[y][x].is_it_chosen = True;
				oldX = x;
				oldY = y;
				Which_one = Board[y][x].Piece_on_square;
				is_it_correct = Help_for_choosing_piece(turn, Which_one);
				is_it_right_move = True;
			} while (!is_it_correct);

			info = "Choose place for your piece";
			ArrowControl(Board, turn, &x, &y, info);
			if (abs(Which_one) == White_King) is_it_correct = King_move((char)x + 97, (char)y + 49, (char)oldY + 49, (char)oldX + 97, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square);
			else if (abs(Which_one) == White_Queen) is_it_correct = Queen_move((char)x + 97, (char)y + 49, (char)oldY + 49, (char)oldX + 97, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board);
			else if (abs(Which_one) == White_Rook) is_it_correct = Rook_move((char)x + 97, (char)y + 49, (char)oldY + 49, (char)oldX + 97, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board);
			else if (abs(Which_one) == White_Knight) is_it_correct = Knight_move((char)x + 97, (char)y + 49, (char)oldY + 49, (char)oldX + 97, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square);
			else if (abs(Which_one) == White_Bishop) is_it_correct = Bishop_move((char)x + 97, (char)y + 49, (char)oldY + 49, (char)oldX + 97, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board);
			else if (abs(Which_one) == White_Pawn) is_it_correct = Pawn_move((char)x + 97, (char)y + 49, (char)oldY + 49, (char)oldX + 97, Board[y][x].Piece_on_square, Board[oldY][oldX].Piece_on_square, Board[oldY][oldX].have_it_been_moved, last_move);
			if (!is_it_correct) is_it_right_move = False;
		} while (!is_it_correct);

		Board[y][x].Piece_on_square = Which_one;
		Board[oldY][oldX].Piece_on_square = Empty;
		Board[oldY][oldX].have_it_been_moved = True;
		Board[oldY][oldX].is_it_chosen = False;

		if (turn == White) turn = Black;
		else turn = White;
		last_move = Board[y][x];
	}
}

int main() {
	char Starting_Menu;
	printf("Hello in chess game, what do you want to do?\n");
	printf("0 -> new game   1 -> continue play from exist file\n\n"); //powitanie i wybor z opcji gier
	scanf("%c", &Starting_Menu);
	switch (Starting_Menu)
		case '0':
	{
		Board_struct** Board = Make_Board();  //utworzenie szachownicy gotowej do rozpoczecia gry
		Player turn = White;
		playing(turn, Board);
	}
	int stop = 10;
}
