#define MAX_LINKS 4

#ifndef LINKSLISTOBJECT_H
#define LINKSLISTOBJECT_H

typedef struct linksListObject{ //Full definition to avoid incomplete type error
    int rows[MAX_LINKS];
    int columns[MAX_LINKS];
    int linkLength;
    char color;
    Direction direction;
} LinksListObject;

typedef enum{
    INVALID = -1,
    NONE = 0,
    VERTICAL = 1,
    HORIZONTAL = 2,
    NW_SE_DIAGONAL = 3,
    NE_SW_DIAGONAL = 4
} Direction;

LinksListObject LLO_sort(LinksListObject link);
int LLO_checkEquality(LinksListObject a, LinksListObject b);
int LLO_checkMembership(LinksListObject link, LinksListObject[ROWS * COLUMNS], int linksListLength);
void LLO_display(LinksListObject link);

#endif