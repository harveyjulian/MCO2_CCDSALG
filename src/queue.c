#include "queue.h"

/* ---------------- Queue helpers (self-implemented, no libs) ---------------- */

void 
queueInit(Queue *q)
{
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

int 
queueIsEmptyQueue *q) 
{
    int empty;

    if (q->count == 0)
    {
        empty = 1;
    } 
    else 
    {
        empty = 0;
    }

    return empty;
}

int 
queuePush(Queue *q, Point p) 
{
    int ok;

    if (q->count >= MAX_QUEUE) 
    {
        ok = 0;
    } 
    else 
    {
        q->data[q->tail] = p;
        q->tail = (q->tail + 1) % MAX_QUEUE;
        q->count = q->count + 1;
        ok = 1;
    }

    return ok;
}

Point 
queuePop(Queue *q) 
{
    Point p = q->data[q->head];
    q->head = (q->head + 1) % MAX_QUEUE;
    q->count = q->count - 1;

    return p;
}
