#include "structures_and_enums.h"
#include"control_and_display.h"
#include"definitions.h"
#include"rlutil.h"
#include"file_support.h"

#include <stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>

void display_Piece(Board_struct** Board, int i, int j) {
	if (abs(Board[i][j].Piece_on_square) == White_King)
		printf(" K");
	else if (abs(Board[i][j].Piece_on_square) == White_Queen)
		printf(" Q");
	else if (abs(Board[i][j].Piece_on_square) == White_Rook)
		printf(" R");
	else if (abs(Board[i][j].Piece_on_square) == White_Bishop)
		printf(" B");
	else if (abs(Board[i][j].Piece_on_square) == White_Knight)
		printf("KN");
	else if (abs(Board[i][j].Piece_on_square) == White_Pawn)
		printf(" P");
	else if (Board[i][j].Piece_on_square == Empty)
		printf("  ");
	setColor(WHITE);
}

void display_letters() {
	for (int p = 0; p < BOARD_SIZE; p++) {
		printf("%c    ", LETTER + p);
	}
}

void display_top_of_row() {
	for (int j = 0; j < BOARD_SIZE; j++) {
		printf("%c%c%c%c%c", LEFT_TOP_EDGE, TOP_EDGE, TOP_EDGE, TOP_EDGE, RIGHT_TOP_EDGE);
	}
}

void display_middle_square(Board_struct** Board, int i, int j, int x, int y, Pieces colour_of_piece) {
	int colour_on_screen1, colour_on_screen2;
	if (colour_of_piece > 0)			// White pieces
	{ colour_on_screen1 = LIGHTCYAN, colour_on_screen2 = YELLOW;
	} else colour_on_screen1 = LIGHTRED, colour_on_screen2 = RED;

		if (Board[i][j].is_it_chosen == True) {
			setColor(colour_on_screen1);
			display_Piece(Board, i, j);
		} 
		else if(i == y && j == x) { 
			if (Board[i][j].Piece_on_square == 0) {
				setColor(WHITE);
				printf(" %c", CURRENT_EMPTY_SQUARE);
			}
			else {
				setColor(colour_on_screen1);
				display_Piece(Board, i, j);
			}
		}
		else if (Board[i][j].Piece_on_square != 0) {
			setColor(colour_on_screen2);
			display_Piece(Board, i, j);
		}
	else printf("  ");
	setColor(WHITE);
}

void display_instructions(Player *turn, char *info) {
	printf(" ");
	display_top_of_row();
	printf("\n   ");
	display_letters(); //letters on the bottom
	printf("\n");
	if (*turn == White)	printf("\n\nWhite's turn\n\n");
	else printf("\n\nBlack's turn\n\n");
	printf("%s\npress any arrow key for controlling, Enter for choosing place\n\npress s key for save\n\n", info);
	printf("K - King, Q - Queen, R - Rook, B - Bishop, KN - Knight, P - Pawn\n");
	setColor(RED);
	printf("Black   ");
	setColor(YELLOW);
	printf("White\n\n");
	setColor(WHITE);
}

void displayChessboard(Board_struct **Board, Player *turn, int x, int y, char* info)
{
	system("cls");
	setColor(WHITE);
	printf("\n   ");
	display_letters(); //letters on the top
	printf("\n");
	for (int i = BOARD_SIZE -1; i >= 0; i--) { // all 8 rows
		printf(" ");
		display_top_of_row(); // top of every row
		printf("\n");
		printf("%d", i + 1);	// number on the left
		for (int j = 0; j < BOARD_SIZE; j++) { // middle
			printf("%c", LEFT_EDGE);			// left barrier
			
			Pieces colour_of_piece;
			if (Board[i][j].Piece_on_square == 0) colour_of_piece = Empty;
			else if (Board[i][j].Piece_on_square > 0) colour_of_piece = White_King;
			else  colour_of_piece = Black_King;
			display_middle_square(Board, i, j, x, y, colour_of_piece);
			printf(" %c", RIGHT_EDGE); 
		} 	printf("%d\n", i + 1);	// number on the right 
	}
	display_instructions(turn, info); // bottom of chessboard
}

void new_cordinate_arrow(int *x, int *y, int * arrow) {
	arrow = getch();

	if (arrow == DOWN_ARROW) {
		if (*y == DOWN_BORDER)
			*y = UP_BORDER;   // move to up border
		else
			*y = *y - 1;		// move down
	}
	else if (arrow == LEFT_ARROW) {
		if (*x == LEFT_BORDER)
			*x = RIGHT_BORDER;   // move to right border
		else
			*x = *x - 1;		// move left
	}
	else if (arrow == RIGHT_ARROW) {
		if (*x == RIGHT_BORDER)
			*x = LEFT_BORDER;   // move to left border
		else
			*x = *x + 1;		// move right
	}
	else if (arrow == UP_ARROW) {
		if (*y == UP_BORDER)
			*y = DOWN_BORDER;   // move to down border
		else
			*y = *y + 1;		// move up
	}
}

void arrow_control(Board_struct **Board, Player *turn, int *x, int *y, char *str1, int *Which_function, 
	Bool *white_King_threatened, Bool *black_King_threatened, Board_struct *last_move){
	int arrow;
	int stop;
	while (1)
	{
		displayChessboard(Board, turn, *x, *y, str1); 
		stop = getch();
		if (stop == 13) // press enter
		{
			return;
		}
		else if (stop == 's') { //press s
			displayChessboard(Board, turn, *x, *y, "Please write the name of file");
			char buf[21];
			scanf("%20s", buf);
			Bool saving = save_to_file(buf, str1, Board, turn, Which_function, white_King_threatened, black_King_threatened,
				last_move);
			if (saving) 
				displayChessboard(Board, turn, *x, *y, "Saved succesfully, please press any key diffrent than arrow");
			else displayChessboard(Board, turn, *x, *y, "Something went wrong, please press any key diffrent than arrow");
			}
		new_cordinate_arrow(x, y, &arrow);
	}
}
