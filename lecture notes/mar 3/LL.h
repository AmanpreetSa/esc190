#if !defined(LL_H)
#define LL_H
typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct LL{
    node *head;
} LL;

void create_node(node **new_node, int data);
void destroy_node(node *node);

void create_list(LL **list);
void destroy_list(LL *list);


void insert_list(LL *list, int data);
void print_list(LL *list);
void delete_list(LL *list, int data);
void delete_list_ind(LL *list, int index);
void destroy_list(LL *list);

#endif
