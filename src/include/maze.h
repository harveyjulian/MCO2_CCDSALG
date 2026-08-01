#ifndef MAZE_H
#define MAZE_H

#include "common.h"

typedef struct {
    char  grid[MAX_DIM][MAX_DIM + 1]; /* +1 for null terminator safety */
    int   rows;
    int   cols;
    Point start;
    Point goal;
    int   loaded;
} Maze;

int loadMaze(char *filename, Maze *m);
int isInBounds(Maze *m, int r, int c);
int isWalkable(Maze *m, int r, int c);

#endif /* MAZE_H */
