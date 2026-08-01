#ifndef UI_H
#define UI_H

#include "maze.h"
#include "search.h"

void printBanner(void);
void printMenu(int mazeLoaded);
void showMetrics(SearchResult *res);
void startSimulation(Maze *m);
void promptForFilename(char *buffer, int size);
int  runMenuLoop(void);

#endif /* UI_H */
