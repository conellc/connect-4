#ifndef AILOGIC_H
#define AILOGIC_H

int aiMove(char* board, int difficulty);
int getOkMove(char *board);
int getRandomMove(char *board);
int getBestMove(char *board, int depth);

#endif