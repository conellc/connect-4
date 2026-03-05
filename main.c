#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Colors for printing
// How to use: printf(RED"This will be red"WHITE) <- put white after to reset color. it works because you can use seperate strings in printf if they are together. printf("this"" works ""too")
#define WHITE "\e[0m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;34m"
#define MAGENTA "\e[1;35m"

#define ROWS 6
#define COLUMNS 7

// Define these so we can change them anytime
#define EMPTYSLOT 'n'
#define YELLOWSLOT 'y'
#define REDSLOT 'r'

// Helper methods
char getBoardSlot(char* board, int row, int column);
void setBoardSlot(char* board, int row, int column, char value);
void changeOutputCoords(int *outputCoords, int row, int column, int value);

// Main methods
void printBoard(char* board);
int checkLinks(char* board, int linkLength, int *lastMove, int *outputCoords); // I can't return an int array but I can modify an int array input
int makeMove(char* board, int column, char turn);
int aiMove(char* board, int difficulty);

int main(){
    // Test to see if makeMove and column check works (You can delete this)
    char test[ROWS][COLUMNS] = {
      {'n', 'n', 'n', 'n', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'n', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'n', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'y', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'y', 'n', 'n', 'n'},
      {'n', 'n', 'n', 'y', 'n', 'n', 'n'}
    };
    int column = 3, linkLength = 4;
    int row = makeMove(&test[0][0], column, 'y');
    int lastMove[2] = {row, column};
    int outputCoords[linkLength][2];
    int won = checkLinks(&test[0][0], linkLength, lastMove, &outputCoords[0][0]);

    return 0;
}

void printBoard(char* board_pointer){

}

// I would recommend making functions comments like what I have for your functions so we know what they do. Explain parameters and what it returns

/* NOT DONE YET, WIP (column check is done)
    *board - the 2d array of the board as a pointer
    linkLength - the length needed to win
    *lastMove[2] - the last move {row, column} as a pointer (I could probably make this not a pointer since I don't change it)
    *outputCoords[linkLength][2] - the coordinates of the winning line. OutputCoords should be arr[linkLength][2] and passed as &arr[0][0]. To use, first check if this returns 1. 
                                   If you want to get the winner (if you aren't using a variable for the turn) you can get the winner by using any of the coords and getting the character at the coord.

    returns 1 if the last move caused a win, 0 otherwise
*/
int checkLinks(char* board, int linkLength, int *lastMove, int *outputCoords){
    /* Could you modify this code to check for an arbitrary length instead of just 4? 
    Instead of returning just who won, you could return an int array with the syntax
    {{{row1, column1}, {row2, column2}...} ... } where it's a 3D array containing 2D
    arrays with the found links containing 1D arrays with the row and column of the circles.            <- I don't know what you mean by this but hopefully the outputCoords parameter works
    
    It looks harder, but it shouldn't be that much of a change to the internal logic you'd have
    to use to find the links anyways. It'll help a lot with the AI.*/


    int i;
    int won = 0;
    int inARow = 1;

    int moveRow = *lastMove;
    int moveCol = *(lastMove + 1);
    char turn = getBoardSlot(board, moveRow, moveCol);

    // Check column
    if (moveRow >= linkLength - 1)
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
                    won = 1;
                    printf("Column win\n"); // Info msg (can be deleted)
                    break;
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
    return won;
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


    return 0;
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