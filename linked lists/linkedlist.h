#if !defined(LINKEDLIST_H)
#define LINKEDLIST_H

typedef struct node{
    struct node* next;
    int data;
} node;

typedef struct LL{
    node* head;
    int size;
} LL;

void create_LL_from_data(LL** p_LL, int* data_arr, int size);
void create_node(node** n, int data);
void LL_append(LL* my_list, int new_elem);
int validate_list_length(LL* my_list, int length);
void delete(LL* my_list, int index);
void insert(LL* my_list, int index, int data);

#endif
