include <stdio.h>
#include <string.h>
#include "maze.h"

/* ---------------- Maze loading ---------------- */
int 
loadMaze(const char *filename, Maze *m) {
    FILE *fp;
    int   ok;
    int   r;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        ok = 0;
    } 
    else 
    {
        if (fscanf(fp, "%d %d", &m->rows, &m->cols) != 2) 
        {
            ok = 0;
        } 
        else if (m->rows < MIN_DIM || m->rows > MAX_DIM ||
                 m->cols < MIN_DIM || m->cols > MAX_DIM) 
        {
            ok = 0;
        } 
        else 
        {
            char line[256];
            int  ch;

            /* consume the rest of the dimension line */
            ch = fgetc(fp);
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(fp);
            }

            r = 0;
            m->start.row = -1;
            m->start.col = -1;
            m->goal.row  = -1;
            m->goal.col  = -1;

            while (r < m->rows && fgets(line, sizeof(line), fp) != NULL) 
            {
                int len = (int)strlen(line);
                int c;

                while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
                {
                    line[len - 1] = '\0';
                    len = len - 1;
                }
                while (len < m->cols) 
                {
                    line[len] = ' ';
                    len = len + 1;
                }
                line[m->cols] = '\0';

                for (c = 0; c < m->cols; c = c + 1) 
                {
                    m->grid[r][c] = line[c];
                    if (line[c] == 'S') 
                    {
                        m->start.row = r;
                        m->start.col = c;
                    } 
                    else if (line[c] == 'G') 
                    {
                        m->goal.row = r;
                        m->goal.col = c;
                    }
                }
                r = r + 1;
            }

            if (r != m->rows || m->start.row == -1 || m->goal.row == -1) 
            {
                ok = 0;
            } 
            else 
            {
                m->loaded = 1;
                ok = 1;
            }
        }
        fclose(fp);
    }
    return ok;
}

int 
isInBounds(Maze *m, int r, int c)
{
    int in;

    if (r >= 0 && r < m->rows && c >= 0 && c < m->cols) {
        in = 1;
    } 
    else 
    {
        in = 0;
    }

    return in;
}

int 
isWalkable(Maze *m, int r, int c)
{
    int walkable;
    char sym = m->grid[r][c];
    
    if (sym == '#') 
    {
        walkable = 0;
    }
    else
    {
        walkable = 1;
    }

    return walkable;
}
