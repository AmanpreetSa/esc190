#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intlist.h"

void create_list_from_data(IntList **p_IntList, int *data_arr, int size)
{
    *p_IntList = (IntList *)malloc(sizeof(IntList));
    (*p_IntList)->data = (int *)malloc(sizeof(int) * size);
    memcpy((*p_IntList)->data, data_arr, sizeof(int)*size); // copies data_arr value into the data field of the struct
    (*p_IntList)->size = size;
    (*p_IntList)->capacity = size;
}

void list_append(IntList *list, int new_elem)
{
    if (list->size == list->capacity){
        list->capacity *= 2;
        list->data = realloc(list->size, list->capacity * sizeof(int));
    }
    list->data[list->size] = new_elem;  // list->size represents the number of elements currently stored in the list
                                        // list->data is an array that holds these elements
                                        // since array indices start at 0, the next spot to append new_elem is at [list->size]
    list->size++;                       // increment by 1 to show size contains one more element
}

void list_insert(IntList *list, int new_elem, int index)
{
    if (list->size == list->capacity){
        list->capacity *= 2;
        list->data = realloc(list->size, list->capacity * sizeof(int));
    }
    memmove(list->data + index + 1, list->data + index, sizeof(int)*size);
    list->data[list->size] = new_elem;
    list->size++;
}

void list_delete(IntList *list, int index)
{
    memove(list->data + index, list->data + index + 1, sizeof(int)*(list->size-index-1));
    list->size--;
}

void list_destroy(IntList *list){
    free(list->data);
    free(list); // free-ing destorys the list
}

int list_get(IntList *list, int i) {
    return list->data[i];
}
