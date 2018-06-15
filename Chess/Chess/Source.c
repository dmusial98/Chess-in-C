#include <stdio.h>
#include <stdlib.h>

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
} Board_struct;

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
			Board[i][j].letter = filling_letter;
			Board[i][j].have_it_been_moved = False;
		} filling_letter++;
	}
	Board =  Fill_Board(Board); //wypelnienie tablicy 
	return Board;
}

Bool first_condition_for_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {
	if (letter_move_to < 'a' || letter_move_to > 'h' || number_move_to < '1' || number_move_to > '8') return False; //sprawdzenie czy pole docelowe istnieje
	if (colour < 0) {
		if (Is_it_empty < 0) return False;
	}
	if (colour > 0) {
		if (Is_it_empty > 0) return False;		//sprawdzenie czy bierka nie zbija bierki swojego koloru
	}
	return True;
}

Bool King_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(letter_move_to, number_move_to, number_move_from, letter_move_from, Is_it_empty, colour)) return False;

		if (abs(letter_move_to - letter_move_from) < 2 && abs(number_move_to - number_move_from) < 2 && (number_move_to != number_move_from && letter_move_to != letter_move_from)) return True;
		return False;
	}

Bool Rook_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(letter_move_to, number_move_to, number_move_from, letter_move_from, Is_it_empty, colour)) return False;

		if ((letter_move_to == letter_move_from || number_move_to == number_move_from) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) return True;
		return False;
	}

Bool Knight_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(letter_move_to, number_move_to, number_move_from, letter_move_from, Is_it_empty, colour)) return False;

	if (abs(number_move_to - number_move_from) == 2 && abs(letter_move_to - letter_move_from) == 1) return True;
	else if (abs(number_move_to - number_move_from) == 1 && abs(letter_move_to - letter_move_from) == 2) return True;
	return False;
}

Bool Bishop_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(letter_move_to, number_move_to, number_move_from, letter_move_from, Is_it_empty, colour)) return False;

	if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) return True;
	return False;
}

Bool Queen_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour) {

	if (!first_condition_for_move(letter_move_to, number_move_to, number_move_from, letter_move_from, Is_it_empty, colour)) return False;

	if ((letter_move_to == letter_move_from || number_move_to == number_move_from) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) return True;
	if (abs(letter_move_from - letter_move_to) == abs(number_move_from - number_move_to) && (number_move_to != number_move_from && letter_move_to != letter_move_from)) return True;
	return False;
}

Bool Pawn_move(char letter_move_to, char number_move_to, char number_move_from, char letter_move_from, Pieces Is_it_empty, Pieces colour, Bool Have_it_been_moved) {

	if (!first_condition_for_move(letter_move_to, number_move_to, number_move_from, letter_move_from, Is_it_empty, colour)) return False;

	if (colour > 0) { //bialy pion
		if (!Have_it_been_moved) {
			if ((number_move_to - number_move_from) == 2 && letter_move_to == letter_move_from) return True;  //pierwszy ruch piona bialego
		}
		else if ((number_move_to - number_move_from) == 1 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //ruch bialym pionem o jedno pole do przodu
		else if ((number_move_to - number_move_from) == 1 && abs(letter_move_from - letter_move_to) == 1 && Is_it_empty < 0) return True; //zbicie w skosie przeciwnika
		}
	if (colour < 0) { //czarny pion
		if (!Have_it_been_moved) {
			if ((number_move_to - number_move_from) == -2 && letter_move_to == letter_move_from) return True;  //pierwszy ruch piona czarnego
		}
		else if ((number_move_to - number_move_from) == -1 && letter_move_to == letter_move_from && Is_it_empty == Empty) return True;  //ruch czarnym pionem o jedno pole do przodu
		else if ((number_move_to - number_move_from) == -1 && abs(letter_move_from - letter_move_to) == 1 && Is_it_empty > 0) return True; //zbicie w skosie przeciwnika
	}
	}



int main() {
	char Starting_Menu;
	printf("\t\tHello in chess game, what do you want to do?\n");
	printf("0 -> new game   1 -> continue play from exist file\n\n"); //powitanie i wybor z opcji gier
	scanf("%c", &Starting_Menu);
	switch (Starting_Menu)
		case '0':
	{
		Board_struct** Board = Make_Board();  //utworzenie szachownicy gotowej do rozpoczecia gry
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) printf("%d", Board[i][j].Piece_on_square);
			printf("\n");
		}
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) printf("%c%c", Board[i][j].number, Board[i][j].letter);
			printf("\n");
		}
		break;
	}
	int stop = 10;
}