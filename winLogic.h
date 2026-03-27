#ifndef WINLOGIC_H
#define WINLOGIC_H

int checkLinks(char* board, int linkLength, int *lastMove, int *outputCoords);
int noPossibleMoves(char *board);

void changeOutputCoords(int *outputCoords, int row, int column, int value);

#endif