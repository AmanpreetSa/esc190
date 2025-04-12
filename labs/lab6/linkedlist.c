#include <stdio.h>
#include <stdlib.h>

void create_node(node** p_n, int data){
    *p_n = (node *)malloc(sizeof(node));
    (*p_n)->data = data;
    (*p_n)->next = NULL;
}

void create_LL_from_data(LL** p_LL, int* data_arr, int size){
    *p_LL = (LL *)malloc(sizeof(LL));
    (*p_LL)->head = NULL;
    (*p_LL)->size = 0;

    node* prev = NULL;
    for (int i = 0; i < size; i++){
        node* cur;
        create_node(&cur, data_arr[i]);
        if (i == 0){
            (*p_LL)->head = cur;
        } else {
            prev->next = cur;
        }
        prev = cur;
        (*p_LL)->size++;
    }
}

void LL_append(LL* my_list, int new_elem){
    node* new_node;
    create_node(&new_node, new_elem);
    
    if (my_list->head == NULL){
        my_list->head = new_node;
    } else {
        node* cur = my_list->head;
        while (cur->next != NULL){
            cur = cur->next;
        }
        cur->next = new_node;
    }
    my_list->size++;
}

int validate_list_length(LL* my_list, int length){
    int count = 0;
    node* cur = my_list->head;
    while (cur != NULL){
        count++;
        cur = cur->next;
    }
    return (count == length);
}

void delete_node(LL* my_list, int index){
    if (index < 0 || index >= my_list->size) return; // invalid index

    node* cur = my_list->head;
    if (index == 0){
        my_list->head = cur->next;
        free(cur);
    } else {
        node* prev = NULL;
        for (int i = 0; i < index; i++){
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        free(cur);
    }
    my_list->size--;
}

void insert(LL* my_list, int index, int data){
    if (index < 0 || index > my_list->size) return; // invalid index

    node* new_node;
    create_node(&new_node, data);

    if (index == 0){
        new_node->next = my_list->head;
        my_list->head = new_node;
    } else {
        node* cur = my_list->head;
        for (int i = 0; i < index - 1; i++){
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
    }
    my_list->size++;
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

void printList(LL* my_list){
    node* cur = my_list->head;
    while (cur != NULL){
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

void freeList(LL* my_list){
    node* cur = my_list->head;
    while (cur != NULL){
        node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(my_list);
}
