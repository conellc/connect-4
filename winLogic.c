#include "winLogic.h"
#include "boardHelper.h"
#include "connect4.h"
#include <stdio.h>

/*
    @param char *board - the 2d array of the board as a pointer
    @param int linkLength - the length needed to win
    @param int *lastMove - the last move {row, column}

    @return 0 - no win, 1 - Column win, 2 - Row win, 3 - left->right diagonal win, 4 - right->left diagonal win
*/
int checkForWin(char* board, int linkLength, int *lastMove) {
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
        for (i = moveRow + 1; i < ROWS; i++) {
            if (getBoardSlot(board, i, moveCol) == turn) {
                inARow++;
                if (inARow >= linkLength) {
                    return 1;
                }
            }
            else {
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
            if (inARow >= linkLength) {
                return 2;
            }
        } else {
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
            if (inARow >= linkLength) {
                return 3;
            }
        } else {
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
            if (inARow >= linkLength) {
                return 4;
            }
        } else {
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