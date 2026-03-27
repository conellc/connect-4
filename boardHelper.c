#include <stdio.h>
#include <stdlib.h>
#include "connect4.h"
#include "boardHelper.h"

void clearBoard(char* board) {
	int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            *(board + i * COLUMNS + j) = ' ';
        }
    }
}

/*
    Copies one board to another so you can modify it without modifying the original.

    @param board1 -> The board to copy from
    @param board2 -> The board to copy to
*/
void copyBoard(char *board1, char *board2) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            setBoardSlot(board2, i, j, getBoardSlot(board1, i, j));
        }
    }
}

/*
    board[i][j] -> getBoardSlot(board, i, j)
*/
char getBoardSlot(char* board, int row, int column) {
    return *(board + row * COLUMNS + column);
}
/*
    board[i][j] = value -> setBoardSlot(board, i, j, value)
*/
void setBoardSlot(char* board, int row, int column, char value) {
    *(board + row * COLUMNS + column) = value;
}

int maxOfInts(int a, int b) {
    return a > b ? a : b;
}

/*
    @param char board -> a pointer to the board
    @param int move -> the column picked
    @param char turn -> the char for what turn it is (YELLOWSLOT or REDSLOT)

    @return The row the piece was placed if it is valid, -1 if it is invalid
*/
int makeMove(char *board, int move, char turn) {
    if (getBoardSlot(board, 0, move) != EMPTYSLOT)
        return -1;

    int columnPos = ROWS - 1;

    while (getBoardSlot(board, columnPos, move) != EMPTYSLOT && columnPos > 0) {
        columnPos--;
    }

    setBoardSlot(board, columnPos, move, turn);
    return columnPos;
}

/*
    @param char board -> pointer to board
    @param int column -> column to get row at

    @return the row that is lowest at a given column
*/
int getRowFromColumn(char *board, int column) {
    int rowPos = ROWS - 1;
    while (getBoardSlot(board, rowPos, column) != EMPTYSLOT && rowPos > 0) {
        rowPos--;
    }
    return rowPos;
}