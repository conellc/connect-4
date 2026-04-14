/*
    Ryan R. ported the printboard that Ethan S. made to print to a file.
*/

#ifndef SAVEBOARD_H
#define SAVEBOARD_H
#include "connect4.h"

void printBoardtoFile(char board[ROWS][COLUMNS], FILE *file);

#endif
