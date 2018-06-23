#include"structures_and_enums.h"
#include"file_support.h"
#include<stdio.h>

Bool save_to_file(char* name_of_file, char* info, Board_struct **Board, Player *turn, int *Which_function) {

	FILE* file_pointer = fopen(name_of_file, "w");
	if (file_pointer == NULL) {
		info = "I can't open the file";
		return False; }

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fwrite(&Board[i][j].Piece_on_square, sizeof(Pieces), 1, file_pointer);
			fwrite(&Board[i][j].number, sizeof(char), 1, file_pointer);
			fwrite(&Board[i][j].letter, sizeof(char), 1, file_pointer);
			fwrite(&Board[i][j].have_it_been_moved, sizeof(Bool), 1, file_pointer);
			fwrite(&Board[i][j].is_it_chosen, sizeof(Bool), 1, file_pointer);
		}
	   }
	fwrite(turn, sizeof(Player), 1, file_pointer);
	fwrite(Which_function, sizeof(int), 1, file_pointer);

	fclose(file_pointer);
	return True;
}

Bool read_from_file(char* name_of_file, char* info, Board_struct **Board, Player* turn, int *Which_function) {
	FILE* file_pointer = fopen(name_of_file, "r");
	if (file_pointer == NULL) {
		info = "I can't open the file";
		return False;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fread(&Board[i][j].Piece_on_square, sizeof(Pieces), 1, file_pointer);
			fread(&Board[i][j].number, sizeof(char), 1, file_pointer);
			fread(&Board[i][j].letter, sizeof(char), 1, file_pointer);
			fread(&Board[i][j].have_it_been_moved, sizeof(Bool), 1, file_pointer);
			fread(&Board[i][j].is_it_chosen, sizeof(Bool), 1, file_pointer);
		}
	}
	fread(turn, sizeof(Player), 1, file_pointer);
	fread(Which_function, sizeof(int), 1, file_pointer);

	fclose(file_pointer);
	return True;

}
