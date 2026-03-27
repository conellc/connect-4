#include "winLogic.h"
#include "boardHelper.h"
#include "connect4.h"
#include <stdio.h>

/*
    @param char *board - the 2d array of the board as a pointer
    @param int linkLength - the length needed to win
    @param int *lastMove - the last move {row, column}
    @param int *outputCoords - the coordinates of the winning line. OutputCoords should be arr[linkLength][2] and passed as &arr[0][0]. To use, first check if this returns 1. 
                                   If you want to get the winner (if you aren't using a variable for the turn) you can get the winner by using any of the coords and getting the character at the coord.

    @return 0 - no win, 1 - Column win, 2 - Row win, 3 - left->right diagonal win, 4 - right->left diagonal win
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
    @param char *board -> pointer to the board

    @return 1 if there are no possible moves on the board (All spots are filled), 0 otherwise.
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
    outputCoords[i][j] = value -> changeOutputCoords(outputCoords, i, j, value)
*/
void changeOutputCoords(int *outputCoords, int row, int column, int value) {
    *(outputCoords + row * 2 + column) = value;
}