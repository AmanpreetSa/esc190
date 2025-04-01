#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

void create_node(node** p_n, int data){
    *p_n = (node *)malloc(sizeof(node));
    (*p_n)->data = data;
    (*p_n)->next = NULL;
}

void create_LL_from_data(LL** p_LL, int* data_arr, int size){
    *p_LL = (LL *)malloc(sizeof(LL));
    (*p_LL)->head = NULL;
    (*p_LL)->size = size;

    int i = 0;
    node* prev = NULL;
    while (i < size){
        node* cur;
        create_node(&cur, data_arr[i]);
        if (i == 0){
            (*p_LL)->head = cur;
        }
        else{
            prev->next = cur;
        }
        prev = cur;
        i++;
    }
}

void LL_append(LL* my_list, int new_elem){
    node* new_node;
    create_node(&new_node, new_elem);
    
    if (my_list->head == NULL){ // if the list is empty
        my_list->head = new_node; // set the head to the new node
    }
    else{
        node* cur = my_list->head; // start at the head
        while (cur->next != NULL){ // while not at the end of the list
            cur = cur->next; // move to the next node
        }
    cur->next = new_node; // set the next of the last node to the new node
    }
    my_list->size++; // increment the size of the list
}

int validate_list_length(LL* my_list, int length){
    int count = 0;
    node* cur = my_list->head; // initalize a pointer, cur, which holds the value of pointer my_list of head which exists in LL struct
    while (cur != NULL){
        count++;
        cur = cur->next;
    }

    if (count == length){
        return 1;
    }
    return 0;
}

p_a = 5;

void delete(LL* my_list, int index){
    node* cur = my_list->head;
    if (index == 0){    // delete the head node (index 0)
        my_list->head = cur->next;
        free(cur);
    }
    else{
        node* prev = NULL;  
        for (int i = 0; i < index; i++){ // traverse LL before one before index (only <, not <=)
            prev = cur;
            cur = cur->next;
        }
        // update the next pointer to skip the node to be deleted
        prev->next = cur->next;
        free(cur);
    }
    mylist->size--; // decrement the size of the list (since we removed the index at node)
}

void insert(LL* my_list, int index, int data){
    node* new_node;
    create_node(&new_node, data);           // allocated memory for new node, set data, and set next to NULL
    if (index == 0){                        // if the index we are inserting at is at index 0
        new_node->next = my_list->head;     // set the next of the new node to the head of the list
        my_list->head = new_node;           // set the head of the list to the new node
    }
    else{
        node* cur = my_list->head;          // start at the head
        for (int i = 0; i < index - 1; i++){ // traverse LL before one before index (only <, not <=)
            cur = cur->next;
        }
        new_node->next = cur->next;         // set the next of the new node to the next of the current node
        cur->next = new_node;               // set the next of the current node to the new node
    }  
}
