#include <stdio.h>
#include <stdlib.h>
#include "hardAILogicHelper.h"
#include "checkLinks.h"
#include "boardHelper.h"
#include "connect4.h"

int* getAllPossibleMoves(char *board){
    int column;
    int* positions = malloc(COLUMNS * sizeof(int));
    for (column = 0; column < COLUMNS; column++){
        positions[column] = getRowFromColumn(board, column);
    }
    return positions;
}

DepthBoard* createNextBoards(DepthBoard* currentBoard, int turn){
    int *movesPtr = getAllPossibleMoves(currentBoard->currentBoard);
    int column;
    DepthBoard* newDepthBoard = malloc(COLUMNS * sizeof(DepthBoard));

    for (column = 0; column < COLUMNS; column++){
        newDepthBoard[column].currentBoard = NULL;
        newDepthBoard[column].previousBoard = NULL;
        for (int i = 0; i < COLUMNS; i++) {
            newDepthBoard[column].nextBoards[i] = NULL;
        }
        if (movesPtr[column] != ROWS - 1){
            newDepthBoard[column].previousBoard = currentBoard;
            char* newBoardPtr = (char*)malloc(ROWS * COLUMNS * sizeof(char));
            copyBoard(currentBoard->currentBoard, newBoardPtr);
            if (turn == 0){
                setBoardSlot(newBoardPtr, movesPtr[column], column, YELLOWSLOT);
            } else {
                setBoardSlot(newBoardPtr, movesPtr[column], column, REDSLOT);
            }
            
            newDepthBoard[column].currentBoard = newBoardPtr;
            newDepthBoard[column].depthRemaining = currentBoard->depthRemaining - 1;
        }
    }
    free(movesPtr);
    return newDepthBoard;
}

DepthBoard* findMove(DepthBoard* originalBoard, int turn){
    if (originalBoard->depthRemaining == 0){
        return NULL;
    }

    DepthBoard* newNextBoards = createNextBoards(originalBoard, turn);
    int i;

    if (newNextBoards != NULL){
        for (i = 0; i < COLUMNS; i++){
            originalBoard->nextBoards[i] = &newNextBoards[i];
        }
    }
    int scores[COLUMNS] = {0};
    for (i = 0; i < COLUMNS; i++){
        if (originalBoard->nextBoards[i] != NULL){
            if (scoreBoard(originalBoard->nextBoards[i]) > scoreBoard(originalBoard))f{
                findMove(originalBoard, turn == 0 ? 1 : 0);
            }
        }
    }



}

int *scoreBoard(char *board){
    LinksListObject* links = checkLinks(board);
    int scores[2] = {0, 0};
    int link;

    for (link = 0; link < ROWS * COLUMNS; link++){
        if (links[link].direction != INVALID){
            switch(links[link].linkLength){
            case 4:
                if (links[link].color == REDSLOT){
                    scores[0] = scores[0] + 100000;
                } else {
                    scores[1] = scores[1] + 100000;
                }
                break;
            case 3:
                if (links[link].color == REDSLOT){
                    scores[0] = scores[0] + 100;
                } else {
                    scores[1] = scores[1] + 100;
                }
                break;
            case 2:
                if (links[link].color == REDSLOT){
                    scores[0] = scores[0] + 10;
                } else {
                    scores[1] = scores[1] + 10;
                }
                break;
            case 1:
                if (links[link].color == REDSLOT){
                    scores[0] = scores[0] + 1;
                } else {
                    scores[1] = scores[1] + 1;
                }
            }
        }
    }
    return scores;
}