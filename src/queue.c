#include "include/queue.h"

/* ---------------- Queue helpers (self-implemented, no libs) ---------------- */

/**
 *  Sets up a new Queue.
 *  @param q The queue to be utilized
 *  @pre The queue already exists 
 */
void 
queueInit(Queue *q)
{
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

/**
 *  Checks if queue is empty.
 *  @param q The queue to be checked
 *  @return 1 if empty, 0 if otherwise
 *  @pre The queue already exists 
 */
int 
queueIsEmptyQueue (Queue *q) 
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

/**
 *  Adds Point p into the queue. 
 *  @param q The queue to be utilized
 *  @param p The Point to be added into the queue
 *  @return 1 if Point p is added successfully, 0 if otherwise
 *  @pre The queue already exists 
 */
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

/**
 *  Removes the last Point from the queue
 *  @param q The queue to be utilized
 *  @return The removed Point  
 *  @pre The queue already exists 
 */
Point 
queuePop(Queue *q) 
{
    Point p = q->data[q->head];
    q->head = (q->head + 1) % MAX_QUEUE;
    q->count = q->count - 1;

    return p;
}
