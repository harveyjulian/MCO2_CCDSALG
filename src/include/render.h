#ifndef RENDER_H
#define RENDER_H

#include "common.h"
#include "maze.h"

void clearScreen(void);
void renderMaze(const Maze *m, Point ratPos, const int visited[MAX_DIM][MAX_DIM],
                 const Point *finalPath, int finalPathLen, int showFinalPath);

#endif /* RENDER_H */
