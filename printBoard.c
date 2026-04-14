/*
    All functions in this file are created by: Ethan S
*/

#include <stdio.h>
#include "printBoard.h"
#include "colors.h"

void printBoard(char board[ROWS][COLUMNS]){
	int rows, cols, bottom, numbers;
	char cell;
	rows = 0;
	cols = 0;
	bottom = 0;
	numbers = 1;

	while (rows < ROWS){

		printf(BLUE"| ");

		while (cols < COLUMNS){
				cell = board[rows][cols];
				if (cell == 'Y')
            		printf(YELLOW"O");
            	else if (cell == 'R')
            		printf(RED"O");
				else
            		printf("%c"RESET, cell);

				printf(BLUE" | ");

			cols++;
		}

		printf("\n");
		rows++;
		cols=0;

	}


	printf(BLUE"+");

	while (bottom < COLUMNS){
		
		printf("---+");
		bottom++;

	}

	printf(RESET"\n");


	printf(" ");

	while (numbers < COLUMNS+1){

		printf(" %d  ", numbers);
		numbers++;

	}

	printf("\n");

}

