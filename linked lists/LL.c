#include "LL.h"
#include <stdlib.h>

// we need to create just one LL
// then chaining how many nodes we need to LL

void create_node(node** p_n, int data){
    *p_n = (node *)malloc(sizeof(node)); // allocate memory for a node (assigns the addresss of the newly allocated node struct to the memory location pointed to by p_n)
    (*p_n)->data = data;
    (*p_n)->next = NULL;
}

void create_LL_from_data(LL** p_LL, int* data_arr, int size){
    *p_LL = (LL *)malloc(sizeof(LL));
    (*p_LL)->head = NULL;
    (*p_LL)->sz = size;

    // now repeately create nodes and add them to the LL
    int i = 0; // notes inserted so far
    node* prev = NULL;
    while (i < size){
        node* cur;
        create_node(&cur, data_arr[i]);
        if (i == 0){
            (*p_LL)->head = cur; // at i = 0, head MUST be set to cur since first node
        }
        else{
            prev->next = cur;
        }
        prev = cur;
        i++;
    }
}
