#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "include/search.h"
#include "include/queue.h"
#include "include/render.h"

/* ------------------- BFS -------------------- */

/**
 *  The code for algorithm Breadth-First Search.
 *  @param m The maze that will be utilized
 *  @param res The result of the BFS
 *  @param animate Determines the illustration of the maze as the Rat moves
 *  @param delayMicros Shows the amount of time spent by the Rat moving
 *  @pre The maze already exists
 *  @note res->elapsedMs only accumulates time spent on the actual BFS
 *        work (popping cells, bookkeeping, goal check, neighbor
 *        expansion). Time spent inside the animate block (rendering,
 *        usleep) is excluded, so elapsedMs stays the same whether or
 *        not animate is on.
 */
void 
runBFS(Maze *m, SearchResult *res, 
       int animate, int delayMicros)
{
    Queue q;
    int dr[4];
    int dc[4];
    int r, c, i;
    long startTicks;
    long endTicks;
    long accumulatedTicks;
    
    /* Direction Vectors */
    dr[0] = -1; dc[0] = 0;
    dr[1] = 1;  dc[1] = 0;
    dr[2] = 0;  dc[2] = -1;
    dr[3] = 0;  dc[3] = 1;
    
    /* Set all cells as not visited first */
    for (r = 0; r < m->rows; r = r + 1)
    {
        for (c = 0; c < m->cols; c = c + 1) 
        {
            res->visited[r][c] = 0;
        }
    }

    res->orderCount     = 0;
    res->cellsExplored  = 0;
    res->found          = 0;
    res->pathLen        = 0;
    accumulatedTicks    = 0;

    queueInit(&q);

    res->visited[m->start.row][m->start.col] = 1;
    res->parent[m->start.row][m->start.col].row = -1;
    res->parent[m->start.row][m->start.col].col = -1;

    queuePush(&q, m->start);

    while (!queueIsEmpty(&q) && !res->found)
    {
        Point cur;
        int d;

        startTicks = (long)clock();

        cur = queuePop(&q);

        res->order[res->orderCount][0] = cur.row;
        res->order[res->orderCount][1] = cur.col;
        res->orderCount = res->orderCount + 1; 
        res->cellsExplored = res->cellsExplored + 1; 

        endTicks = (long)clock();
        accumulatedTicks = accumulatedTicks + (endTicks - startTicks);

        if (animate)
        {
            Point ratPos;

            ratPos.row = cur.row;
            ratPos.col = cur.col;

            clearScreen();

            printf("Exploring maze with BFS...\n\n");

            renderMaze(m, ratPos, res->visited, NULL, 0, 0);

            printf("\nCells explored so far: %d\n", res->cellsExplored);

            fflush(stdout);
            usleep(delayMicros);
        }

        /* Resume the clock for the rest of the internal BFS step. */
        startTicks = (long)clock();

        if (cur.row == m->goal.row && cur.col == m->goal.col)
        {
            res->found = 1;
        } 
        else 
        {
            for (d = 0; d < 4; d = d + 1)
            {
                int nr = cur.row + dr[d];
                int nc = cur.col + dc[d];

                if (isInBounds(m, nr, nc) && isWalkable(m, nr, nc) &&
                    !res->visited[nr][nc]) 
                {
                    Point next;
                    next.row = nr;
                    next.col = nc;
                    res->visited[nr][nc] = 1;
                    res->parent[nr][nc].row = cur.row;
                    res->parent[nr][nc].col = cur.col;
                    queuePush(&q, next);
                }
            }
        }

        endTicks = (long)clock();
        accumulatedTicks = accumulatedTicks + (endTicks - startTicks);
    }

    res->elapsedMs = ((double)accumulatedTicks / CLOCKS_PER_SEC) * 1000.0;

    if (res->found) 
    {
        Point cur = m->goal;
        int   count = 0;
        Point buffer[MAX_QUEUE];

        while (cur.row != -1)
        {
            buffer[count] = cur;
            count = count + 1;
            cur = res->parent[cur.row][cur.col];
        }

        for (i = 0; i < count; i = i + 1) {
            res->path[i] = buffer[count - 1 - i];
        }
        res->pathLen = count;
    }
}
