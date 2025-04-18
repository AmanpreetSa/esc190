#include <stdio.h>

// Q1
int my_median(int* arr, int sz)
{
    qsort(arr, sz, sizeof(int), compar);
    return arr[sz/2];
}

int compar(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

// Q2
void count_letters(char* s, int counts[])
{
    for (int i = 0; i < 26; i++) {
        counts[i] = 0;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            counts[s[i] - 'a']++;
        }
    }
}

// Q3 
char* reverse_words(char* str)
{
    // Step 1: Make a copy of the input string (since input should not be changed)
    int len = strlen(str)+1;
    char* copy = (char*)malloc(sizeof(char) * (len));
    strcpy(copy, str);

    char* words[100];
    int word_count = 0;

    char* token = strtok(copy, " ");
    while (token != NULL) {                     // strtok() returns null NULL if has no more tokens to extract from string
        words[word_count] = token;              
        token = strtok(NULL, " ");              // finds the next word (if no next turn, returns NULL)
        word_count++;                           // we just added an word to the words[] array, increment the word 
    }

    // Step 4: Build the reversed result string
    char* result = (char*)malloc(sizeof(char) * (len));
    result[0] = '\0';

    for (int i = word_count - 1; i >= 0; i--) {
        strcat(result, words[i]);
        if (i > 0) {
            strcat(result, " ");
        }
    }

    free(copy);
    return result;
}

// Q4
int is_increasing(int *arr, int sz)
{
    if (sz == 0) {
        return 1;
    }
    if (sz == 1) {
        return 1; 
    }
    if (arr[0] >= arr[1]) {
        return 0;
    }
    return is_increasing(arr+1, sz-1);
}

// Q5
typedef struct CircularQueue {
    int start, end, size, num_elements;
    char** arr;
} CircularQueue;

void create(CircularQueue** p_cq, int size)
{
    *p_cq = (CircularQueue*)malloc(sizeof(CircularQueue));
    (*p_cq)->start = 0;
    (*p_cq)->end = 0;
    (*p_cq)->size = size;
    (*p_cq)->num_elements = 0;
    (*p_cq)->arr = (char**)malloc(sizeof(char*) * size);
}

void enqueue(CircularQueue* cq, const char* data)
{
    if (cq->num_elements == cq->size) {
        cq->arr = (char**)realloc(cq->arr, 2 * sizeof(char*) * cq->size);
        if (cq->end < cq->start) {
            memmove(cq->arr + cq->size, cq->arr, cq->end * sizeof(char*));
            cq->end += cq->size;
        }
        cq->size *= 2;
    }

    int len = strlen(data) + 1;
    char* copy = (char*)malloc(sizeof(char) * len);
    strcpy(copy, data);

    (cq->arr)[cq->end] = copy;
    cq->end = (cq->end + 1) % cq->size;
    cq->num_elements++;
}

void dequeue(CircularQueue* cq)
{
    if (cq->num_elements == 0) {
        return;
    }

    free(cq->arr[cq->start]);
    cq->start = (cq->start + 1) % cq->size;
    cq->num_elements--;
}

void destroy(CircularQueue* cq) {
    for (int i = 0; i < cq->num_elements; i++) {
        int idx = (cq->start + i) % cq->size;
        free(cq->arr[idx]);
    }
    free(cq->arr);
    free(cq);
}

