#include "boardHelper.h"
#include "connect4.h"
#include "aiLogic.h"
#include <stdlib.h>
#include "winLogic.h"
#include "checkLinks.h"
#include "hardAILogicHelper.h"
#include "printBoard.h"
#include <stdio.h>

int aiMove(char* board_pointer, int difficulty){
    int choice;
    
    if (difficulty == 1){
      choice = -1;
    } else if (difficulty == 2){
      choice = getOkMove(board_pointer);
    } else if (difficulty - 300 > 0){
      choice = getBestMove(board_pointer, difficulty - 300);
    } else if (difficulty == 4){
      choice = -1; // Change this to call your impossible function
    }

    if (choice < 0 || choice >= COLUMNS){ // Fallback for invalid choice (Chooses random move)
      choice = getRandomMove(board_pointer);
    }
    return choice;
}

int getOkMove(char *board) {
    char boardA[ROWS][COLUMNS];
    char *boardPtr = &boardA[0][0];
    copyBoard(board, boardPtr);

    int choices[COLUMNS];
    int i, col, row, win, links;
    char slot;

    for (i = 0; i < COLUMNS; i++) {
        choices[i] = 0;
    }

    for (links = 4; links > 1; links--) {
        for (col = 0; col < COLUMNS; col++) {
            for(i = 0; i < 2; i++) {
                copyBoard(board, boardPtr);
                slot = i == 0 ? YELLOWSLOT : REDSLOT;
                row = makeMove(boardPtr, col, slot);
                if (row == -1) continue;
                int move[] = {row, col};
                win = checkForWin(boardPtr, links, &move[0]);
                if (win > 0) {
                    choices[col] += links * (links == 4 ? 4 : 1);
                }
            }
        }
    }

    int maxIndex = 0, sum = choices[0];
    for (i = 1; i < COLUMNS; i++) {
        int a = maxOfInts(choices[maxIndex], choices[i]);
        if (choices[maxIndex] != a) maxIndex = i;
        sum += choices[i];
    }
    if (sum == 0) return -1;
    return maxIndex;
}

int getRandomMove(char *board) {
    char boardA[ROWS][COLUMNS];
    char *boardPtr = &boardA[0][0];
    copyBoard(board, boardPtr);

    int choice;
    do {
        choice = rand() % COLUMNS;
    }
    while (makeMove(boardPtr, choice, REDSLOT) == -1);
    return choice;
}

int getBestMove(char *board, int depth){
    int choice = 0;
    int i;
    DepthBoard* originalBoard = malloc(sizeof(DepthBoard));
    
    originalBoard->currentBoard = (char*)malloc(ROWS * COLUMNS * sizeof(char));
    copyBoard(board, originalBoard->currentBoard);
    originalBoard->previousBoard = NULL;
    originalBoard->depthRemaining = depth;
    
    for (i = 0; i < COLUMNS; i++) {
        originalBoard->nextBoards[i] = NULL;
    }
    
    choice = findMove(originalBoard, 1);

    return choice;
}