#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    int data;
} node;

typedef struct LL {
    node* head;
    int size;
} LL;

void create_node(node** p_n, int data)
{
    *p_n = (node*)malloc(sizeof(node));
    (*p_n)->next = NULL;
    (*p_n)->data = data;
}

void create_LL_from_data(LL** p_LL, int* data_arr, int size)
{
    *p_LL = (LL*)malloc(sizeof(LL));
    (*p_LL)->head = NULL;
    (*p_LL)->size = 0;

    node* prev = NULL;
    for (int i = 0; i < size; i++) {
        node* cur;
        create_node(&cur, data_arr[i]);
        if (i == 0) {
            (*p_LL)->head = cur;
        }
        else {
            prev->next = cur;
        }
        prev = cur;
        (*p_LL)->size++;
    }
}

void append(LL* list, int new_val)
{
    node* new_node;
    create_node(&new_node, new_val);

    if (list->head == NULL) {
        list->head = new_node; 
    }
    else {
        node* cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_node;
    }
    list->size++;
}

void delete(LL* list, int i)
{
    if (i < 0 || i > list->size) {
        return 0;
    }

    node* cur = list->head;
    if (i == 0) {
        list->head = cur->next;
        free(cur);
    }
    else {
        node* prev = NULL;
        for (int j = 0; j < i; j++) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        free(cur);
    }
    list->size--;
}

void insert(LL* list, int data, int i) 
{
    if (i < 0 || i >= list->size) {
        return 0;
    }

    node* new_node;
    create_node(&new_node, data);

    if (i == 0) {
        new_node->next = list->head;
        list->head = new_node;
    }
    else {
        node* cur = list->head;
        for (int j = 0; j < i-1; j++) {
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
    }
    list->size++;
}

int search(LL* my_list, int target){
    node* cur = my_list->head;
    int index = 0;
    while (cur != NULL){
        if (cur->data == target) return index;
        cur = cur->next;
        index++;
    }
    return -1; // not found
}
