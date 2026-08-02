#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/ui.h"
#include "include/render.h"
#include "include/search.h"

/* ---------------- UI / Menu ---------------- */

/**
 *  Prints separator.
 */
void
separator1()
{
    printf("*************************************** \n");
}

/**
 *  Prints the menu section.
 *  @param mazdeLoaded Detemines whether the maze is already loaded
 *  @pre The maze already exists
 */
void
printMenu(int mazeLoaded)
{
    printf("[1] Start Simulator \n");
    printf("[2] Load File \n");
    printf("[3] Quit \n");
    printf("\n");
}

/**
 *  Prints the name of the simulator, which is RAT SIMULATOR.
 */
void
printBanner(void)
{
    separator1();
    printf("RAT SIMULATOR\n");
    separator1();
}

/**
 *  Displays the details of the details of the path result from the maze.
 *  @param res The result of the BFS algorithm in the maze
 *  @pre The maze already exists and the BFS already executed
 */
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

/**
 *  Starts simulating the maze and goes through the BFS algorithm.
 *  @param m The maze being utilized.
 *  @pre The maze already exists
 */
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
            printf("PATH FOUND!!! Following it... Look at this:\n\n");
            renderMaze(m, res.path[i], res.visited, res.path, i + 1, 1);
            fflush(stdout);
            usleep(100000);
        }
    }
    else
    {
        Point none;

        printf("BFS finished exploring, but no path exists... :((( \n\n");
        none.row = -1;
        none.col = -1;

        renderMaze(m, none, res.visited, NULL, 0, 0);
    }

    showMetrics(&res);
}

/**
 *  Searches the maze file.
 *  @param buffer Where the file's name will be put
 *  @param size The length of the file's name
 *  @pre The file already exists
 */
void
promptForFilename(char *buffer, int size) {
    printf("Enter maze filename: ");
    scanf("%255s", buffer);
    getchar();
}

/**
 *  Runs the simulator starting from the menu.
 *  @return 1 when the program ended, 0 if otherwise
 *  @pre The maze already exists and the BFS already executed
 */
int
runMenuLoop()
{
    Maze m;
    int running;
    int exitStatus;
    int choice;
    char filenameBuf[256];

    m.loaded = 0;
    running = 1;
    exitStatus = 0;

    while (running)
    {
        clearScreen();
		printBanner();
		
        if (m.loaded)
        {
            printf("Current maze loaded (%d x %d).\n", m.rows, m.cols);
        }

        separator1();
        printMenu(m.loaded);
        separator1();

        printf(">> ");
        scanf("%d", &choice);

        while (choice != 1 && choice != 2 && choice != 3)
        {
            printf("Invalid input! Press Enter to try again... \n");
            while (getchar() != '\n');

            separator1();
            printf(">> ");
            scanf("%d", &choice);
        }

        switch (choice)
        {
            case 1:
                if (m.loaded) 
				{
                    startSimulation(&m);
                } 
				else 
				{
                    printf("\nNo maze loaded yet. Please load one first.\n");
                }
				
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                break;

            case 2:
                clearScreen();
                printBanner();
                printf("\n");
				
                promptForFilename(filenameBuf, sizeof(filenameBuf));
				
                if (loadMaze(filenameBuf, &m)) 
				{
                    printf("\nMaze loaded successfully!\n");
                } 
				else 
				{
                    printf("\nFailed to load maze! Check the filename, dimensions ");
                    printf("(%d-%d), and that thee \"S\" and \"G\" are presenk.\n", MIN_DIM, MAX_DIM);
                }
				
                printf("\nPress Enter to continue...");
                getchar();
                break;

            case 3:
                printf("\nGoodbye!\n");
                running = 0;
                break;
        }
    }

    return exitStatus;
}
