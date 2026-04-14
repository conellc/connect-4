/*
    Ryan R. ported the printboard that Ethan S. made to print to a file.
*/

#include <stdio.h>
#include "saveBoard.h"

void printBoardtoFile(char board[ROWS][COLUMNS], FILE *file){
	int rows, cols, bottom, numbers;
	char cell;
	rows = 0;
	cols = 0;
	bottom = 0;
	numbers = 1;

	while (rows < ROWS){

		fprintf(file, "| ");

		while (cols < COLUMNS){
				cell = board[rows][cols];
				if (cell == 'Y')
            		fprintf(file, "Y");
            	else if (cell == 'R')
            		fprintf(file, "R");
				else
            		fprintf(file, "%c", cell);

				fprintf(file, " | ");

			cols++;
		}

		fprintf(file, "\n");
		rows++;
		cols=0;

	}


	fprintf(file, "+");

	while (bottom < COLUMNS){
		
		fprintf(file, "---+");
		bottom++;

	}

	fprintf(file, "\n");


	fprintf(file, " ");

	while (numbers < COLUMNS+1){

		fprintf(file, " %d  ", numbers);
		numbers++;

	}

	fprintf(file, "\n");

}

