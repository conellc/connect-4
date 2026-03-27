#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "printBoard.h"
#include "colors.h"
#include "connect4.h"

int getColumn();
int getOkMove(char *board);
int getRandomMove(char *board);
int getAIMode();
void clearBoard(char* board);

// Main methods
int checkLinks(char* board, int linkLength, int *lastMove, int *outputCoords);
int makeMove(char *board, int move, char turn);
int aiMove(char* board, int difficulty);
int noPossibleMoves(char *board);
int getRowFromColumn(char *board, int column);
// Helper methods
char getBoardSlot(char* board, int row, int column);
void setBoardSlot(char* board, int row, int column, char value);
void changeOutputCoords(int *outputCoords, int row, int column, int value);
void copyBoard(char *board1, char *board2);
int maxOfInts(int a, int b);

int main(){
	srand(time(NULL));

	char board[ROWS][COLUMNS];
    char* boardPtr = &board[0][0];
    clearBoard(boardPtr);

    int turn = 0;
    
    int rowPos, requiredInARow = 4;
    int outputCoords[requiredInARow][2];
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
                move = aiMove(boardPtr, aiDiff);
                rowPos = getRowFromColumn(boardPtr, move);
            }
        }
        rowPos = makeMove(boardPtr, move, turn == 0 ? YELLOWSLOT : REDSLOT);
        if (rowPos == -1) {
            printf("Invalid move: %d, %d\n", rowPos, move);
            continue;
        }
        
        int lastMove[2] = {rowPos, move};

        if (checkLinks(boardPtr, requiredInARow, &lastMove[0], &outputCoords[0][0]) >= 1) { // Check for win
            printBoard(board);
            printf("%s wins!\n"WHITE, turn == 0 ? YELLOW"Yellow" : RED"Red");
            break;
        } else if (noPossibleMoves(boardPtr)) { // If board is filled it is a draw
            printBoard(board);
            printf("The game ended in a draw.");
            break;
        }
        turn = (turn + 1) % 2;
    }
    return 0;
}


/*
    *board - the 2d array of the board as a pointer
    linkLength - the length needed to win
    lastMove[2] - the last move {row, column}
    *outputCoords[linkLength][2] - the coordinates of the winning line. OutputCoords should be arr[linkLength][2] and passed as &arr[0][0]. To use, first check if this returns 1. 
                                   If you want to get the winner (if you aren't using a variable for the turn) you can get the winner by using any of the coords and getting the character at the coord.

    returns: 0 - no win, 1 - Column win, 2 - Row win, 3 - left->right diagonal win, 4 - right->left diagonal win
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
    board -> pointer to the board

    returns 1 if there are no possible moves on the board (All spots are filled), 0 otherwise.
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
    char board -> pointer to board
    int column -> column to get row at

    returns the row that is lowest at a given column
*/
int getRowFromColumn(char *board, int column) {
    int rowPos = ROWS - 1;
    while (getBoardSlot(board, rowPos, column) != EMPTYSLOT && rowPos > 0) {
        rowPos--;
    }
    return rowPos;
}

/*
    char board -> a pointer to the board
    int move -> the column picked
    char turn -> the char for what turn it is (YELLOWSLOT or REDSLOT)

    returns -1 if the move is invalid, returns the row the piece was placed if it is valid
*/
int makeMove(char *board, int move, char turn) {
    if (getBoardSlot(board, 0, move) != EMPTYSLOT)
        return -1;

    int columnPos = ROWS - 1;

    while (getBoardSlot(board, columnPos, move) != EMPTYSLOT && columnPos > 0) {
        columnPos--;
    }

    setBoardSlot(board, columnPos, move, turn);
    return columnPos;
}

int aiMove(char* board_pointer, int difficulty){
    int choice;
    
    if (difficulty == 1){
      choice = -1;
    } else if (difficulty == 2){
      choice = getOkMove(board_pointer);
    } else if (difficulty == 3){
      choice = -1;
    } else if (difficulty == 4){
      choice = -1;
    }  
    if (choice == -1){
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
                int outputCoords[links][2];
                win = checkLinks(boardPtr, links, &move[0], &outputCoords[0][0]);
                if (win > 0) choices[col] += links * (links == 4 ? 4 : 1); // If 2, 4 in a rows can be made make own first
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

// Helper methods start
/*
    board[i][j] -> getBoardSlot(board, i, j)
*/
char getBoardSlot(char* board, int row, int column) {
    return *(board + row * COLUMNS + column);
}
/*
    board[i][j] = value -> setBoardSlot(board, i, j, value)
*/
void setBoardSlot(char* board, int row, int column, char value) {
    *(board + row * COLUMNS + column) = value;
}
/*
    outputCoords[i][j] = value -> changeOutputCoords(outputCoords, i, j, value)
*/
void changeOutputCoords(int *outputCoords, int row, int column, int value) {
    *(outputCoords + row * 2 + column) = value;
}

/*
    Copies one board to another so you can modify it without modifying the original.

    board1 -> The board to copy from
    board2 -> The board to copy to
*/
void copyBoard(char *board1, char *board2) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            setBoardSlot(board2, i, j, getBoardSlot(board1, i, j));
        }
    }
}

// Returns the max of 2 ints
int maxOfInts(int a, int b) {
    return a > b ? a : b;
}

void clearBoard(char* board) {
	int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            *(board + i * COLUMNS + j) = ' ';
        }
    }
}
int getColumn() {
    printf("Enter a column to place your piece: ");
    int n;
    scanf("%d", &n);
    while (n < 1 || n > COLUMNS) {
        printf("Enter a number between 1 and %d: ", COLUMNS);
        while (getchar() != '\n');
        scanf("%d", &n);
    }
    return n - 1;
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

int getAIMode() {
    char duelAI;
    printf("Do you want to duel an AI (y/n)? ");
    scanf(" %c", &duelAI);
    while (duelAI != 'y' && duelAI != 'n') {
        printf("Please put 'y' or 'n': ");
        while (getchar() != '\n');
        scanf(" %c", &duelAI);
    }
    if (duelAI == 'n') return -1;

    int n;
    printf("What mode should it be?\n1. Easy\n2. Normal\n3. Hard\n4. Difficult\n ");
    scanf("%d", &n);
    while (n < 1 || n > 4) {
        printf("Enter a number between 1 and %d: ", COLUMNS);
        while (getchar() != '\n');
        scanf("%d", &n);
    }
    return n;
}
