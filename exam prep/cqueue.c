// #if !defined(CQ_H)
// #define CQ_H

// typedef struct CircularQueue {
//     int start, end, size, num_elements;
//     int* arr;
// } CircularQueue;

// void create(CircularQueue **p_cq, int size);
// void destory(CircularQueue *cq);
// void enqueue(CircularQueue *cq, int data);
// void dequeue(CircularQueue *cq);

#include "cqueue.h"
#include <stdlib.h>
#include <stdio.h>

void create(CircularQueue **p_cq, int size)
{
    *p_cq = (CircularQueue*)malloc(sizeof(CircularQueue));
    (*p_cq)->start = 0;
    (*p_cq)->end = 0;
    (*p_cq)->size = size;
    (*p_cq)->num_elements = 0;
    (*p_cq)->arr = (int*)malloc(size * sizeof(int));
}

void destory(CircularQueue *cq)
{
    free(cq->arr); // first free cq->arr to free array, THEN free(cq);
    free(cq);
}

void enqueue(CircularQueue *cq, int data)
{
    if (cq->num_elements == cq->size) {
        cq->arr = (int*)realloc(cq->arr, 2 * cq->size * sizeof(int));
        if (cq->end < cq->start) {
            // Only move elements if the queue has wrapped around
            memmove(cq->arr + cq->size, cq->arr, cq->end * sizeof(int));
            cq->end += cq->size;
        }
        cq->size *= 2;
    }

    (cq->arr)[cq->end] = data;
    cq->end = (cq->end + 1) % cq->size;
    cq->num_elements++;
}

void dequeue(CircularQueue *cq)
{
    if (cq->num_elements == 0) {
        return;
    }
    
    cq->start = (cq->start + 1) % cq->size;
    cq->num_elements--;
}

void print_CircularQueue(CircularQueue* cq)
{
    int i = cq->start;
    int count = 0;
    while (count < cq->num_elements) {
        printf("%d\n", cq->arr[i]);
        i = (i + 1) % cq->size;
        count++;
    }
}