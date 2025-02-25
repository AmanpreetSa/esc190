#if !defined(LL_H)

typedef struct node{
    struct node* next;  // contain link to the next node (must include struct node* to avoid error)
    int data;   
} node;

typedef struct LL{
    node* head;         // contain link to the first node
    int sz;             // the size
} LL;

void create_LL_from_data(LL** p_LL, int* data_arr, int size);
void create_node(node** n, int data);

#endif
