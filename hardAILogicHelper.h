#ifndef HARDAILOGICHELPER_H
#define HARDAILOGICHELPER_H
#include "connect4.h"

typedef struct depthBoard{
    char* currentBoard;
    struct depthBoard* previousBoard;
    struct depthBoard* nextBoards[COLUMNS];
    int depthRemaining;
} DepthBoard;

int* getAllPossibleMoves(char *board);
int* scoreBoard(char *board);
DepthBoard* createNextBoards(DepthBoard *currentBoard, int turn);
DepthBoard* findMove(DepthBoard *originalBoard, int turn);

#endif