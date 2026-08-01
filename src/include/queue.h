#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

typedef struct {
    Point data[MAX_QUEUE];
    int   head;
    int   tail;
    int   count;
} Queue;

void  queueInit(Queue *q);
int   queueIsEmpty(const Queue *q);
int   queuePush(Queue *q, Point p);
Point queuePop(Queue *q);

#endif /* QUEUE_H */
