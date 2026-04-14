/*
    Functions by: Ryan R.
*/

#ifndef BOARDHELPER_H
#define BOARDHELPER_H

void copyBoard(char *board1, char *board2);
char getBoardSlot(char* board, int row, int column);
void setBoardSlot(char* board, int row, int column, char value);
void clearBoard(char* board);
int maxOfInts(int a, int b);
int makeMove(char *board, int move, char turn);
int getRowFromColumn(char *board, int column);

#endif