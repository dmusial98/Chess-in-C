#ifndef FILE_SUPPORT_H
#define FILE_SUPPORT_H

Bool save_to_file(char* name_of_file, char* info, Board_struct **Board, Player *turn, int *Which_function);
//saving actual state of game to file

Bool read_from_file(char* name_of_file, char* info, Board_struct **Board, Player* turn, int *Which_function);
//reading a game from file

#endif