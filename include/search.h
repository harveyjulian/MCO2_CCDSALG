#ifndef SEARCH_H
#define SEARCH_H

#include "common.h"
#include "maze.h"

typedef struct {
    int    visited[MAX_DIM][MAX_DIM];
    Point  parent[MAX_DIM][MAX_DIM];
    int    order[MAX_QUEUE][2];   /* sequence of cells explored, for animation */
    int    orderCount;
    Point  path[MAX_QUEUE];
    int    pathLen;
    int    cellsExplored;
    int    found;
    double elapsedMs;
} SearchResult;

void runBFS(const Maze *m, SearchResult *res, int animate, int delayMicros);

#endif /* SEARCH_H */
