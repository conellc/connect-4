#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "printBoard.h"
#include "colors.h"
#include "connect4.h"
#include "userInput.h"
#include "aiLogic.h"
#include "boardHelper.h"
#include "winLogic.h"
#include "saveBoard.h"

int main(){
	srand(time(NULL));

	char board[ROWS][COLUMNS];
    char* boardPtr = &board[0][0];
    clearBoard(boardPtr);

    int turn = 0;
    
    int rowPos, requiredInARow = 4;
    int move;

    int aiDiff = getAIMode(); // AI difficulty, -1 is no AI.

    while (1) {
        if ((aiDiff != -1 && turn == 0) || aiDiff == -1) { // If its AI and the player's turn or 2 player.
            printBoard(board);
            printf("\n");
        }
        if (aiDiff < 0) { // If its not AI
            printf("%s's turn\n", turn == 0 ? "Yellow" : "Red"); // Turn 0 is yellow, turn 1 is red
            move = getColumn();
        } else { // If it is AI
            if (turn == 0) { // If its the player's turn
                printf("Your turn\n");
                move = getColumn();
            } else { // If its the AI's turn
                if (aiDiff == 1){getRandomMove(boardPtr);}
                if (aiDiff == 2){getOkMove(boardPtr);}
                if (aiDiff - 300 > 0){getBestMove(boardPtr, checkLinks(boardPtr), aiDiff - 300);} //Make sure to free links in getBestMove()
                rowPos = getRowFromColumn(boardPtr, move);
            }
        }
        rowPos = makeMove(boardPtr, move, turn == 0 ? YELLOWSLOT : REDSLOT);
        if (rowPos == -1) {
            printf("Invalid move: %d, %d\n", rowPos, move);
            continue;
        }
        
        int lastMove[2] = {rowPos, move};

        if (checkForWin(boardPtr, requiredInARow, &lastMove[0]) >= 1) { // Check for win
            printBoard(board);
            printf("%s wins!\n"WHITE, turn == 0 ? YELLOW"Yellow" : RED"Red");
            break;
        } else if (noPossibleMoves(boardPtr)) { // If board is filled it is a draw
            printBoard(board);
            printf("The game ended in a draw.\n");
            break;
        }
        turn = (turn + 1) % 2;
    }

    char saveBoard;
    printf("Do you want to save the board? (y/n): ");
    scanf(" %c", &saveBoard);
    getchar();
    if (saveBoard == 'y') {
        char name[50];
        printf("Enter winner name: ");
        fgets(name, 50, stdin);
        FILE *file = fopen("saved_board.txt", "w");
        fprintf(file, "Player Name: %s\nBoard State:\n", name);
        printBoardtoFile(board, file);
        fclose(file);
    }

    return 0;
}