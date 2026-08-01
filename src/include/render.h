#ifndef RENDER_H
#define RENDER_H

#include "common.h"
#include "maze.h"

void clearScreen(void);
void renderMaze(Maze *m, Point ratPos, int visited[MAX_DIM][MAX_DIM],
                 Point *finalPath, int finalPathLen, int showFinalPath);

#endif /* RENDER_H */
