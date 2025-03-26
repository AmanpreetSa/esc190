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

// linked list: 1->2->3->4->5
// ArrayList: [1, 2, 3, 4, 5]

// append("insert"): can access index 5 immeditaitely (with arithmetic)
//                   but you need to possibily reallocate the whole array
//                   and move it
// In the worst case, complexity is O(n), where n is the number of elements

// To the linked list: can "append" to the beginning
// O(1) (just make the head point to the new node, make the new node point to the old head)

// Queue ADT (abstract data type)

// Queue: a list with FIFO (First In/First Out) operations
//        no random access
//        (random access: ability to get any element by index)
// operations:
// 1. enqueue: add an element to the end of the queue
// 2. dequeue: remove the first element from the queue

// ENQUEUE 5
// ENQUEUE 6
// ENQUEUE 1
            // queue: 5 6 1
// DEQUEUE (output: 5)
// DEQUEUE (output: 6)
            // queue: 1
// ENQUEUE 2
            // queue: 1 2
// DEQUEUE (output: 1)
// DEQUEUE (output: 2)

// [5, 6, 10, 2]
// in the worst case enqueue is O(n), usually less than that
// every time, dequeue is O(n) because need to move
// L[1:] all spots to the left after removing at index 0 every time 

// if using a linked list based implentation, data will look like this:

head->5->6->10->2->NULL
// can insert next to the head in O(1) time
// if you can keep track of where the last node is,
// can also append in O(1)
