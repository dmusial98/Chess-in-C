#include "structures_and_enums.h"
#include "making_chessboard.h"
#include "control_and_display.h"
#include "play_support.h"
#include"danger_of_King.h"
#include"definitions.h"
#include"moves.h"
#include"support_checkmate.h"
#include"support_for_moves.h"
#include"file_support.h"

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>

void timer(int sekundy) {		//function waiting writing time in seconds
	int czas = 1000 * sekundy;
	clock_t poczatek = clock();
	while (clock() < poczatek + czas);
}

void choose_game(char *choose) {
	while (*choose < '0' || *choose > '1') {
		system("cls");
		printf("Please write correct number\n0 -> start new game\t1-> play from excisting file\n");
		*choose = getchar();
	}
}

void switch_game(char choose) {
	Player turn;
	int Which_function;
	switch (choose) {
	case '0': {
		Board_struct** Board = Make_Board();
		Board = Fill_Board(Board);
		turn = White;
		Player who_won = playing(&turn, Board, &Which_function);
		if (who_won == White) displayChessboard(Board, &turn, 0, 0, "White pieces won\n\n");
		else displayChessboard(Board, &turn, 0, 0, "Black pieces won\n\n");
		break;
	}
	case '1': {
		Board_struct **Board = Make_Board();
		char *info = "Hello";
		printf("\nplease write name of file\n");
		char buf[21];
		scanf("%20s", buf);
		Bool black_King_threatened, white_King_threatened, is_it_correct, possible_move;
		int x = 0, y = 0, oldX = 0, oldY = 0; //position and old position
		Pieces Which_one, What_was_there;
		Board_struct last_move;
		Bool reading = read_from_file(buf, info, Board, &turn, &Which_function, &white_King_threatened,
			&black_King_threatened, &last_move);
		if (reading) info = "\nRead succesfully";
		else printf("\nSomething went wrong");
		if (Which_function == 0)
		{
			Player who_won = playing(&turn, Board, &Which_function);
			//resuming the game from state without check(danger of King)
		}
		else if (Which_function == 1) {// resuming the game in check state
			support_for_condition_from_check(&black_King_threatened, &is_it_correct, &possible_move,
				&white_King_threatened, &oldX, &oldY, &x, &y, &Which_one, &last_move, Board, info,
				&What_was_there, &turn, &Which_function, True);
			if (turn == White) turn = Black;
			else turn = White;
			Player who_won = playing(&turn, Board, &Which_function);
			//playing after obviating check (danger of King)

			if (who_won == White) displayChessboard(Board, &turn, 0, 0, "White pieces won\n\n");
			else displayChessboard(Board, &turn, 0, 0, "Black pieces won\n\n");
			for (int i = 0; i < BOARD_SIZE; i++) {
				free(Board[i]);
			}
			free(Board);
			break;
		}
		printf(", please open game anew");
	}
	}
}

int main(int argc, char* argv[]) {

	printf("Hello in chess game, what do you want to do?\n 0 -> start new game\t1-> play from existing file\n");
	char choose = getchar();
	choose_game(&choose);
	switch_game(choose);

	timer(200);
	return 0;
}
