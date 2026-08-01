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
separator1()
{
	printf("*************************************** \n");
}

/**
 *  Displays the main menu of the simulator.
 *  @param mazeLoaded Determines if the maze is already loaded
 *  @pre The maze is loaded already
 */
void
printMenu(int mazeLoaded)
{
    printf("RAT SIMULATOR \n");
    printf("\n");
    printf("[1] Start Simulator \n");
    printf("[2] Load File \n");
    printf("[3] Quit \n");
    printf("\n");
}

/**
 *  Displays the result of the simulator.
 *  @param res The result of the maze simulator
 *  @pre The result already exists
 */
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

/**
 *  Showcases the simulation.
 *  @param m The maze being utilized
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
 *  Finds the filename for the maze.
 *  @param buffer Where the maze filename will be stored
 *  @param size -
 */
void
promptForFilename(char *buffer, int size) {
    printf("Enter maze filename: ");
    scanf("%255s", buffer);
    getchar();
}

/**
 *  [insert desc]
 *  @param m ---
 *  @return 1 if , 0 if otherwise
 */
int 
runMenuLoop() {
    Maze m;
    int running;
    int exitStatus;
    int choice;
    char name;
    int size;

    m.loaded = 0;
    running = 1;
    exitStatus = 0;
    
    //continue

    if(m.loaded == 1)
    {
        separator1();
        printMenu(m.loaded);
        separator1();

        printf(">> ");
    	scanf("%d", &choice);

        while(choice != 1 && choice != 2 && choice != 3)
	    {
		    printf("Invalid input! Press Enter to try again... \n");
    		while(getchar() != '\n');
            getchar();
            choice = 0; 
        
            separator1();
            printf(">> ");
		    scanf("%d", &choice);
	    }

        if(choice == 1)
    	{
            promptForFilename(&name, size);
			startSimulation(&m);
            
	    }
    	else if(choice == 2)
		{
            loadMaze(&name, &m);
	    }
    	else if(choice == 3)
        {
		    printf("\n");
		    printf("Leaving the simulator. Thank you!!!");
	    }

    }


 }
