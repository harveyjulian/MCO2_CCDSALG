#include <stdio.h>
#include "include/render.h"

/* ---------------- Rendering ---------------- */

/**
 *  Clears the screen.
 */
void 
clearScreen()
{
    printf("\033[2J\033[H");
}

/**
 *  Renders the maze.
 *  @param m The maze that will be utilized
 *  @param ratPos Shows the position of the Rat
 *  @param visited Shows the cells already visited by the Rat
 *  @param finalPath The path taken by the Rat
 *  @param finalPathLen The length of the path taken by the Rat
 *  @param showFinalPath The path of the WINNING path
 *  @pre The maze already exists
 */
void 
renderMaze(Maze *m, Point ratPos, int visited[MAX_DIM][MAX_DIM],
           Point *finalPath, int finalPathLen, int showFinalPath) 
{
    int r, c; //row and col
    int i;
    int onFinalPath = 0;
    char sym;

    printf("█");
    for (c = 0; c < m->cols; c = c + 1) {
        printf("█");
    }
    printf("█\n");

    for (r = 0; r < m->rows; r = r + 1) {
        printf("█");
        for (c = 0; c < m->cols; c = c + 1) {
            sym = m->grid[r][c];
            onFinalPath = 0;

            if (showFinalPath) {
                for (i = 0; i < finalPathLen; i = i + 1) {
                    if (finalPath[i].row == r && finalPath[i].col == c) {
                        onFinalPath = 1;
                    }
                }
            }

            if (r == ratPos.row && c == ratPos.col && onFinalPath)
            {
                printf("\033[31m\u2588\033[0m"); // red block
            } 
            else if (sym == 'G') 
            {
                printf("\033[32m\u2588\033[0m"); // green block
            } 
            else if (sym == 'S') 
            {
                printf("S");
            } 
            else if (onFinalPath)
            {
                printf("\033[92m*\033[0m"); //neon green asterisk
            } 
            else if (sym == '#') 
            {
                printf("█");
            } 
            else if (visited[r][c]) 
            {
                printf(".");
            } 
            else 
            {
                printf(" ");
            }
        }
        printf("█\n");
    }

    printf("█");

    for (c = 0; c < m->cols; c = c + 1)
    {
        printf("█");
    }

    printf("█\n");
}
