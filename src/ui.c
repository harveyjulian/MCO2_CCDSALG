#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/ui.h"
#include "include/render.h"
#include "include/search.h"

/* ---------------- UI / Menu ---------------- */

void
printMenu(int mazeLoaded)
{
    printf("RAT SIMULATOR \n");
    printf("\n");
    printf("[1] Start Simulator \n");
    printf("[2] Load File \n");
    printf("[3] Quit \n");
    printf("\n");
    printf(">>");
}

/* For post-simulation display */
void
showMetrics(SearchResult *res) {
    printf("\n--- SEARCH METRICS ---\n");

    if (res->found)
        printf("Goal reached!\n");
    else
        printf("No path found.\n");

    printf("Total cells explored : %d\n", res->cellsExplored);
    printf("Final path length    : %d\n", res->pathLen);
    printf("Execution time       : %.3f ms\n", res->elapsedMs);
}

void
startSimulation(Maze *m)
{
    SearchResult res;
    int i;

    runBFS(m, &res, 1, 80000);

    clearScreen();

    if (res.found)
    {
        for (i = 0; i < res.pathLen; i = i + 1)
        {
            clearScreen();
            printf("PATH FOUND!!!! Following it. Look at this:\n\n");
            renderMaze(m, res.path[i], res.visited, res.path, i + 1, 1);
            fflush(stdout);
            usleep(100000);
        }
    }
    else
    {
        Point none;
        printf("BFS finished exploring, but no path exists :((( \n\n");
        none.row = -1;
        none.col = -1;
        renderMaze(m, none, res.visited, NULL, 0, 0);
    }

    showMetrics(&res);
}

void
promptForFilename(char *buffer, int size) {
    printf("Enter maze filename: ");
    scanf("%255s", buffer);
    getchar();
}

int 
runMenuLoop() {
    Maze m;
    int  running;
    int  exitStatus;
    int  choice;

    m.loaded = 0;
    running = 1;
    exitStatus = 0;
    
    //continue
 }
