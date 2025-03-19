#include "q.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    queue *q;
    create_queue(&q);
    enqueue(q, 5);
    enqueue(q, 1);
    enqueue(q, 2);
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    destroy_queue(q);
}