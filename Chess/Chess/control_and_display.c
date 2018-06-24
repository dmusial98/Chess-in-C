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
	setColor(WHITE);
}

void displayChessboard(Board_struct **Board, Player *turn, int x, int y, char* info)
{
	system("cls");
	setColor(WHITE);
	printf("\n   ");
	for (int p = 0; p < 8; p++) {
		printf("%c    ", 65 + p);		// letters on the top
	}
	printf("\n");
	for (int i = 7; i >= 0; i--) { // all 8 rows
		printf(" ");
		for (int j = 0; j < 8; j++) {	// top of every row
			printf("%c", 195);	printf("%c", 196); printf("%c", 196); printf("%c", 196); printf("%c", 180);
		}
		printf("\n");
		printf("%d", i + 1);	// number on the left
		for (int j = 0; j < 8; j++) { // middle
			printf("%c", 124);			// left barrier

			if (Board[i][j].Piece_on_square > 0)			// White pieces
			{
				if (Board[i][j].is_it_chosen == True) {
					setColor(LIGHTCYAN);
					display_Piece(Board, i, j);
				}
				else {
					if (i == y && j == x)  setColor(LIGHTCYAN);
					else setColor(YELLOW);	
					display_Piece(Board, i, j);
				}
			}
			else if (Board[i][j].Piece_on_square < 0)	// Black pieces
			{
				if (Board[i][j].is_it_chosen == True) {
					setColor(LIGHTRED);		//colour for displaying chosen piece
					display_Piece(Board, i, j);
				}
				else {
					if (i == y && j == x) setColor(LIGHTRED);
					else setColor(RED);	//colour of the rest of black pieces
					display_Piece(Board, i, j);
				}
			}
			else if (i == y && j == x)
				printf(" %c", 176);
			else printf("  ");

			printf(" %c", 124);
		} 	printf("%d\n", i + 1);	// number on the right 
	}
	// bottom of chessboard
	printf(" ");
	for (int i = 0; i < 8; i++) {
		printf("%c", 195); printf("%c", 196);	printf("%c", 196); printf("%c", 196);	 printf("%c", 180);
	}
	printf("\n   ");
	for (int p = 0; p < 8; p++) {
		printf("%c    ", 65 + p);		// letters on the bottom
	}
	printf("\n");
	if (*turn == 1)	printf("\n\nWhite's turn\n\n");
	else printf("\n\nBlack's turn\n\n");
	printf("%s\npress any arrow key for controlling\n\npress s key for save\n\n", info);
	printf("K - King, Q - Queen, R - Rook, B - Bishop, KN - Knight, P - Pawn\n");
	setColor(RED);
	printf("Black   ");
	setColor(YELLOW);
	printf("White\n\n");
	setColor(WHITE);
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
		else if (stop == 's') {
			displayChessboard(Board, turn, *x, *y, "Please write the name of file");
			char buf[21];
			scanf("%20s", buf);
			Bool saving = save_to_file(buf, str1, Board, turn, Which_function, white_King_threatened, black_King_threatened,
				last_move);
			if (saving) 
				displayChessboard(Board, turn, *x, *y, "Saved succesfully, please press any key diffrent than arrow");
			else displayChessboard(Board, turn, *x, *y, "Something went wrong, please press any key diffrent than arrow");
			}
		arrow = getch();

		if (arrow == DOWN_ARROW) {
			if (*y == DOWN_BORDER)
				*y = UP_BORDER;   // move to up border
			else
				*y = *y - 1;		// move down
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
			if (*y == UP_BORDER)
				*y = DOWN_BORDER;   // move to down border
			else
				*y = *y + 1;		// move up
		}
	}
}
