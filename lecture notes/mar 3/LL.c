#include "LL.h"
#include <stdlib.h>
#include <stdio.h>

// void create_node(node **new_node, int data);
// void destroy_node(node *node);

// void create_list(LL **list);
// void destroy_list(LL *list);

// void insert(LL *list, int data);
// void print(LL *list);
// void delete(LL *list, int data);
// void destroy(LL *list);

void create_node(node **new_node, int data){
    *new_node = (node *)malloc(sizeof(node));
    (*new_node)->data = data;
    (*new_node)->next = NULL;
}

void destroy_node(node *node){
    free(node);
}

void create_list(LL **list){
    *list = (LL *)malloc(sizeof(LL));
    (*list)->head = NULL;
}

void destroy_list(LL *list){
    node *current = list->head;
    node *next;
    while(current != NULL){
        next = current->next;
        destroy_node(current);
        current = next;
    }
    free(list);
}

void insert_list(LL *list, int data){
    node *new_node;
    create_node(&new_node, data);
    new_node->next = list->head;
    list->head = new_node;
}

void print_list(LL *list){
    node *current = list->head;
    while(current != NULL){
        printf("%d", current->data);
        current = current->next;
        if(current != NULL){
            printf(" -> ");
        }
    }
    printf("\n");
}

void delete_list(LL *list, int data){
    node *current = list->head;
    node *prev = NULL;
    while(current != NULL){
        if(current->data == data){
            if(prev == NULL){
                list->head = current->next;
            }else{
                prev->next = current->next;
            }
            destroy_node(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void delete_list_ind(LL *list, int index){
    node *current = list->head;
    node *prev = NULL;
    int i = 0;
    while(current != NULL){
        if(i == index){
            if(prev == NULL){
                list->head = current->next;
            }else{
                prev->next = current->next;
            }
            destroy_node(current);
            return;
        }
        prev = current;
        current = current->next;
        i++;
    }
}