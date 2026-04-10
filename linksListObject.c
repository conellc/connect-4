#include <stdio.h>
#include "connect4.h"
#include "linksListObject.h"

/* Sorts LLO positions by their rows, or by their columns if it's horizontal. */
LinksListObject LLO_sort(LinksListObject link){
    LinksListObject sortedLink = link;
    int i;
    int j;
    int lowest;
    int lowest_index;
    int last_lowest = -1;

    if (link.direction != HORIZONTAL){
        for (i = 0; i < link.linkLength; i++){
            lowest = ROWS;
            for (j = 0; j < link.linkLength; j++){
                if (link.rows[j] < lowest && link.rows[j] > last_lowest){
                    lowest = link.rows[j];
                    lowest_index = j;
                }
            }
            sortedLink.rows[i] = link.rows[lowest_index];
            sortedLink.columns[i] = link.columns[lowest_index];
            last_lowest = lowest;

        }
    } else {
        for (i = 0; i < link.linkLength; i++){
            lowest = COLUMNS;
            for (j = 0; j < link.linkLength; j++){
                if (link.columns[j] < lowest && link.columns[j] > last_lowest){
                    lowest = link.columns[j];
                    lowest_index = j;
                }
            }
            sortedLink.rows[i] = link.rows[lowest_index];
            sortedLink.columns[i] = link.columns[lowest_index];
            last_lowest = lowest;

        }
    }
    return sortedLink;
}

/*
Checks if two LinksListObjects are equal.
NOTE: the two LLOs are expected to be sorted. Pass through LLO_sort() before use.
*/
int LLO_checkEquality(LinksListObject a, LinksListObject b){
    if (a.linkLength != b.linkLength || a.color != b.color || a.direction != b.direction){
        return -1;
    }
    int i;
    for (i = 0; i < MAX_LINKS; i++){
        if (a.rows[i] != b.rows[i] || a.columns[i] != b.columns[i]){
            return -1;
        }
    }
    return 0;
}

/*
Checks if the LinksListObject belongs to the LLO list.
NOTE: the two LLOs are expected to be sorted. Pass through LLO_sort() before use.
*/
int LLO_checkMembership(LinksListObject link, LinksListObject linksList[ROWS * COLUMNS], int linksListLength){
    int i;
    for (i = 0; i < linksListLength; i++){
        if (LLO_checkEquality(link, linksList[i]) == 0){
            return 0;
        }
    }
    return -1;
}

/*Prints information about the LinksListObject to the console.*/
void LLO_display(LinksListObject link){
    int i;
    printf("----------\n");
    printf("Positions: ");
    for (i = 0; i < MAX_LINKS; i++){
        printf("(%d, %d) ", link.rows[i], link.columns[i]);
    }
    printf("\nLink Length: %d\n", link.linkLength);
    printf("Color: %c\n", link.color);
    printf("Direction: %d\n", link.direction);
    printf("----------\n");
}