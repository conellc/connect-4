#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "colors.h"

#define ROWS 6
#define COLUMNS 7

// Define these so we can change them anytime
#define EMPTYSLOT 'n'
#define YELLOWSLOT 'y'
#define REDSLOT 'r'

// Main methods
void printBoard(char* board);
int checkLinks(char* board, int linkLength, int *lastMove, int *outputCoords);
int makeMove(char *board, int move, char turn);
int aiMove(char* board, int difficulty);
int noPossibleMoves(char *board);
int getRowFromColumn(char *board, int column);

// Helper methods
char getBoardSlot(char* board, int row, int column);
void setBoardSlot(char* board, int row, int column, char value);
void changeOutputCoords(int *outputCoords, int row, int column, int value);
void copyBoard(char *board1, char *board2);
int maxOfInts(int a, int b);

int main(){
    srand(time(NULL));
    // Test to see if makeMove and column check works (You can delete this)
    char test[ROWS][COLUMNS] = {
      {'y', 'n', 'n', 'n', 'n', 'n', 'n'},
      {'n', 'y', 'n', 'n', 'n', 'n', 'n'},
      {'n', 'n', 'y', 'n', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'n', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'r', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'y', 'n', 'n', 'n'}
    };
    int column = 3, linkLength = 4;
    int row = makeMove(&test[0][0], column, 'y');
    int lastMove[2] = {row, column};
    int outputCoords[linkLength][2];
    int won = checkLinks(&test[0][0], linkLength, lastMove, &outputCoords[0][0]);
    printf("%d\n", won);

    return 0;
}

void printBoard(char* board_pointer){

}

/*
    *board - the 2d array of the board as a pointer
    linkLength - the length needed to win
    lastMove[2] - the last move {row, column}
    *outputCoords[linkLength][2] - the coordinates of the winning line. OutputCoords should be arr[linkLength][2] and passed as &arr[0][0]. To use, first check if this returns 1. 
                                   If you want to get the winner (if you aren't using a variable for the turn) you can get the winner by using any of the coords and getting the character at the coord.

    returns: 0 - no win, 1 - Column win, 2 - Row win, 3 - left->right diagonal win, 4 - right->left diagonal win
*/
int checkLinks(char* board, int linkLength, int *lastMove, int *outputCoords) {
    // Check win based on last move
    int i;
    int won = 0;
    int inARow = 1;

    int moveRow = *lastMove;
    int moveCol = *(lastMove + 1);
    char turn = getBoardSlot(board, moveRow, moveCol);
    
    // Check column
    if (moveRow >= linkLength - 1) // Optimization
        won = 0;
    else {
        changeOutputCoords(outputCoords, 0, 0, moveRow);
        changeOutputCoords(outputCoords, 0, 1, moveCol);
        for (i = moveRow + 1; i < ROWS; i++) {
            if (getBoardSlot(board, i, moveCol) == turn) {
                inARow++;
                changeOutputCoords(outputCoords, inARow - 1, 0, i);
                changeOutputCoords(outputCoords, inARow - 1, 1, moveCol);
                if (inARow >= linkLength) {
                    return 1;
                }
            }
            else {
                for (i = 0; i < linkLength; i++) {
                    changeOutputCoords(outputCoords, i, 0, 0);
                    changeOutputCoords(outputCoords, i, 1, 0);
                }
                break;
            }
        }
    }
    // Check column end
    
    moveRow = *lastMove;
    moveCol = *(lastMove + 1);
    inARow = 0;

    // Check row
    while (moveCol > 0) {
        moveCol--;
        if (getBoardSlot(board, moveRow, moveCol) != turn) {
            moveCol++;
             break;
        }
    }

    for (i = moveCol; i < COLUMNS; i++) {
        if (getBoardSlot(board, moveRow, i) == turn) {
            inARow++;
            changeOutputCoords(outputCoords, inARow - 1, 0, moveRow);
            changeOutputCoords(outputCoords, inARow - 1, 1, i);
            if (inARow >= linkLength) {
                return 2;
            }
        } else {
            for (i = 0; i < linkLength; i++) {
                changeOutputCoords(outputCoords, i, 0, 0);
                changeOutputCoords(outputCoords, i, 1, 0);
            }
            break;
        }
    }
    // Check row end

    moveRow = *lastMove;
    moveCol = *(lastMove + 1);
    inARow = 0;

    // Check left->right diagonal
    while (moveRow > 0 && moveCol > 0) {
        moveRow--;
        moveCol--;
        if (getBoardSlot(board, moveRow, moveCol) != turn) {
            moveRow++;
            moveCol++;
            break;
        }
    }

    for (i = 0; moveRow + i < ROWS && moveCol + i < COLUMNS; i++) {
        if (getBoardSlot(board, moveRow + i, moveCol + i) == turn) {
            inARow++;
            changeOutputCoords(outputCoords, inARow - 1, 0, moveRow + i);
            changeOutputCoords(outputCoords, inARow - 1, 1, moveCol + i);
            if (inARow >= linkLength) {
                return 3;
            }
        } else {
            for (i = 0; i < linkLength; i++) {
                changeOutputCoords(outputCoords, i, 0, 0);
                changeOutputCoords(outputCoords, i, 1, 0);
            }
            break;
        }
    }
    // Check left->right diagonal end

    moveRow = *lastMove;
    moveCol = *(lastMove + 1);
    inARow = 0;

    // Check right->left diagonal
    while (moveRow > 0 && moveCol < COLUMNS - 1) {
        moveRow--;
        moveCol++;
        if (getBoardSlot(board, moveRow, moveCol) != turn) {
            moveRow++;
            moveCol--;
            break;
        }
    }

    for (i = 0; moveRow + i < ROWS && moveCol - i >= 0; i++) {
        if (getBoardSlot(board, moveRow + i, moveCol - i) == turn) {
            inARow++;
            changeOutputCoords(outputCoords, inARow - 1, 0, moveRow + i);
            changeOutputCoords(outputCoords, inARow - 1, 1, moveCol - i);
            if (inARow >= linkLength) {
                return 4;
            }
        } else {
            for (i = 0; i < linkLength; i++) {
                changeOutputCoords(outputCoords, i, 0, 0);
                changeOutputCoords(outputCoords, i, 1, 0);
            }
            break;
        }
    }
    // Check right->left diagonal end

    return won;
}

/*
    board -> pointer to the board

    returns 1 if there are no possible moves on the board (All spots are filled), 0 otherwise.
*/
int noPossibleMoves(char *board) {
    int i;
    for (i = 0; i < COLUMNS; i++) {
        if (getBoardSlot(board, 0, i) == EMPTYSLOT)
            return 0;
    }
    return 1;
}

/*
    char board -> pointer to board
    int column -> column to get row at

    returns the row that is lowest at a given column
*/
int getRowFromColumn(char *board, int column) {
    int rowPos = ROWS - 1;
    while (getBoardSlot(board, rowPos, column) != EMPTYSLOT && rowPos > 0) {
        rowPos--;
    }
    return rowPos;
}

/*
    char board -> a pointer to the board
    int move -> the column picked
    char turn -> the char for what turn it is (YELLOWSLOT or REDSLOT)

    returns -1 if the move is invalid, returns the row the piece was placed if it is valid
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

int aiMove(char* board_pointer, int difficulty){


    return 0;
}

// Helper methods start
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
/*
    outputCoords[i][j] = value -> changeOutputCoords(outputCoords, i, j, value)
*/
void changeOutputCoords(int *outputCoords, int row, int column, int value) {
    *(outputCoords + row * 2 + column) = value;
}

/*
    Copies one board to another so you can modify it without modifying the original.

    board1 -> The board to copy frmo
    board2 -> The board to copy to
*/
void copyBoard(char *board1, char *board2) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            setBoardSlot(board2, i, j, getBoardSlot(board1, i, j));
        }
    }
}

// Returns the max of 2 ints
int maxOfInts(int a, int b) {
    return a > b ? a : b;
}