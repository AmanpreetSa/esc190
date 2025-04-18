#if !defined(CQ_H)
#define CQ_H

typedef struct CircularQueue {
    int start, end, size, num_elements;
    int* arr;
} CircularQueue;

void create(CircularQueue **p_cq, int size);
void enqueue(CircularQueue *cq, int data);
void dequeue(CircularQueue *cq);
void destory(CircularQueue *cq);

#endif
