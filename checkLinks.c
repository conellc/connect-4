#include <stdio.h>
#include <stdlib.h>
#include "connect4.h"
#include "linksListObject.h"
#include "boardHelper.h"

/*Gives a list of the links on the board.*/
LinksListObject* checkLinks(char* board){

    LinksListObject* linksList = malloc(ROWS * COLUMNS * sizeof(LinksListObject));
    int linkCounter = 0; //The number of links currently in linksList.
    int row = 0;
    int column = 0;
    char color;
    int linkRow = 0;
    int linkColumn = 0;
    int oneLengthLink = 0; //0 if the slot has no same-color neighbors, 1 otherwise
    LinksListObject baseLinkConstructor = {{0}, {0}, 0, 0, 0}; //template for baseLink we need to have because of struct initialization weirdness
    for (row = 0; row < MAX_LINKS; row++){
        baseLinkConstructor.rows[row] = -1;
        baseLinkConstructor.columns[row] = -1;
    }

    for (row = 0; row < ROWS; row++){
        for (column = 0; column < COLUMNS; column++){
            
            color = getBoardSlot(board, row, column);
            if (color == EMPTYSLOT){
                continue;
            }

            LinksListObject baseLink = baseLinkConstructor;
            baseLink.rows[baseLink.linkLength] = row;
            baseLink.columns[baseLink.linkLength] = column;
            baseLink.linkLength++;
            baseLink.color = color;
            oneLengthLink = 0;

            //Column check ------------------------------------------------------------
            LinksListObject currentLink = baseLink;
            currentLink.direction = 1;
            linkRow = row;
            for (linkRow = row; linkRow > 0; linkRow--){
                if (getBoardSlot(board, linkRow - 1, column) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = linkRow - 1;
                    currentLink.columns[currentLink.linkLength] = column;
                    currentLink.linkLength++;
                } else {
                    break;
                }
            }
            for (linkRow = row; linkRow < ROWS; linkRow++){
                if (getBoardSlot(board, linkRow + 1, column) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = linkRow + 1;
                    currentLink.columns[currentLink.linkLength] = column;
                    currentLink.linkLength++;
                } else {
                    break;
                }
            }
            if (currentLink.linkLength > 1){
                currentLink = LLO_sort(currentLink);
                oneLengthLink = 1;
                if (LLO_checkMembership(currentLink, linksList, linkCounter) == -1){
                    linksList[linkCounter] = currentLink;
                    linkCounter++;
                }
            }

            //Row check -----------------------------------------------------------
            currentLink = baseLink;
            currentLink.direction = 2;
            linkColumn = column;
            for (linkColumn = column; linkColumn > 0; linkColumn--){
                if (getBoardSlot(board, row, linkColumn - 1) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = row;
                    currentLink.columns[currentLink.linkLength] = linkColumn - 1;
                    currentLink.linkLength++;
                } else {
                    break;
                }
            }
            for (linkColumn = column; linkColumn < COLUMNS; linkColumn++){
                if (getBoardSlot(board, row, linkColumn + 1) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = row;
                    currentLink.columns[currentLink.linkLength] = linkColumn + 1;
                    currentLink.linkLength++;
                } else {
                    break;
                }
            }
            if (currentLink.linkLength > 1){
                currentLink = LLO_sort(currentLink);
                oneLengthLink = 1;
                if (LLO_checkMembership(currentLink, linksList, linkCounter) == -1){
                    linksList[linkCounter] = currentLink;
                    linkCounter++;
                }
            }

            //NW/SE diagonal check --------------------------------------------------------
            currentLink = baseLink;
            currentLink.direction = 3;
            linkRow = row;
            linkColumn = column;
            while (linkRow > 0 && linkColumn > 0){
                if (getBoardSlot(board, linkRow - 1, linkColumn - 1) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = linkRow - 1;
                    currentLink.columns[currentLink.linkLength] = linkColumn - 1;
                    currentLink.linkLength++;
                    linkRow--;
                    linkColumn--;
                } else {
                    break;
                }
            }
            linkRow = row;
            linkColumn = column;
            while (linkRow < ROWS && linkColumn < COLUMNS){
                if (getBoardSlot(board, linkRow + 1, linkColumn + 1) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = linkRow + 1;
                    currentLink.columns[currentLink.linkLength] = linkColumn + 1;
                    currentLink.linkLength++;
                    linkRow++;
                    linkColumn++;
                } else {
                    break;
                }
            }
            if (currentLink.linkLength > 1){
                currentLink = LLO_sort(currentLink);
                oneLengthLink = 1;
                if (LLO_checkMembership(currentLink, linksList, linkCounter) == -1){
                    linksList[linkCounter] = currentLink;
                    linkCounter++;
                }
            }

            //NE/SW diagonal check --------------------------------------------------------
            currentLink = baseLink;
            currentLink.direction = 4;
            linkRow = row;
            linkColumn = column;
            while (linkRow > 0 && linkColumn < COLUMNS){
                if (getBoardSlot(board, linkRow - 1, linkColumn + 1) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = linkRow - 1;
                    currentLink.columns[currentLink.linkLength] = linkColumn + 1;
                    currentLink.linkLength++;
                    linkRow--;
                    linkColumn++;
                } else {
                    break;
                }
            }
            linkRow = row;
            linkColumn = column;
            while (linkRow < ROWS && linkColumn > 0){
                if (getBoardSlot(board, linkRow + 1, linkColumn - 1) == currentLink.color){
                    currentLink.rows[currentLink.linkLength] = linkRow + 1;
                    currentLink.columns[currentLink.linkLength] = linkColumn - 1;
                    currentLink.linkLength++;
                    linkRow++;
                    linkColumn--;
                } else {
                    break;
                }
            }
            if (currentLink.linkLength > 1){
                currentLink = LLO_sort(currentLink);
                oneLengthLink = 1;
                if (LLO_checkMembership(currentLink, linksList, linkCounter) == -1){
                    linksList[linkCounter] = currentLink;
                    linkCounter++;
                }
            }
            //--------------------------------------------------------------------------

            if (oneLengthLink == 0){
                linksList[linkCounter] = baseLink;
                linkCounter++;
            }
            
        }
    }


    //Fill all of linksList with invalid links
    int i;
    int j;
    for (i = linkCounter; i < ROWS * COLUMNS; i++){
        for (j = 0; j < MAX_LINKS; j++){
            linksList[i].rows[j] = -1;
            linksList[i].columns[j] = -1;
        }
        linksList[i].linkLength = 0;
        linksList[i].color = EMPTYSLOT;
        linksList[i].direction = -1;
    }
    return linksList;
}