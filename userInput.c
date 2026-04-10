#include <stdio.h>
#include "connect4.h"
#include "userInput.h"
#include "colors.h"

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
    printf("What mode should it be?\n"
           "1. "GREEN"Easy"RESET"\n"
           "2. "YELLOW"Normal"RESET"\n"
           "3. "RED"Hard"RESET"\n"
           "4. "MAGENTA"Impossible"RESET"\n "
        );
    scanf("%d", &n);
    while (n < 1 || n > 4) {
        printf("Enter a number between 1 and %d: ", COLUMNS);
        while (getchar() != '\n');
        scanf("%d", &n);
    }
    return n;
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