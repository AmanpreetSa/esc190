#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

int lexi_sort(const void* a, const void* b){
    const term* t1 = (const term*)a;
    const term* t2 = (const term*)b;
    return strcmp(t1->term, t2->term);
}

int weightsort(const void *a, const void *b) {
    const term *t1 = (const term *)a;
    const term *t2 = (const term *)b;
    if (t1->weight > t2->weight) return -1;
    if (t1->weight < t2->weight) return 1;
    return 0;
}

void read_in_terms(term **terms, int *pnterms, char *filename){
    FILE *fp = fopen(filename, "r");    // assume file opens
    char line[200];
    fgets(line, sizeof(line), fp);      // read number of terms from FILE *fp
    *pnterms = atoi(line);              // convert first line to int
    *terms = (term *)malloc(sizeof(term) * (*pnterms));

    for (int i = 0; i < *pnterms; i++){
        fgets(line, sizeof(line), fp);
        sscanf(line, "%lf %[^\n]", &(*terms)[i].weight, (*terms)[i].term);
    }
    qsort(*terms, *pnterms, sizeof(term), lexi_sort);
    fclose(fp);
}

int lowest_match(struct term *terms, int nterms, char *substr){
    int left = 0;
    int right = nterms - 1; 
    int result = -1;
    int len = strlen(substr);

    while (left <= right){
        int mid = (left + right) / 2;
        int cmp = strncmp(terms[mid].term, substr, len);    // compare first len characters of term to substr

        if (cmp < 0){
            left = mid + 1;
        } else if (cmp > 0){
            right = mid - 1;
        } else {
            result = mid;
            right = mid - 1;
        }
    }
    return result;
}

int highest_match(struct term *terms, int nterms, char *substr){
    int left = 0;
    int right = nterms - 1; 
    int result = -1;
    int len = strlen(substr);

    while (left <= right){
        int mid = (left + right) / 2;
        int cmp = strncmp(terms[mid].term, substr, len);    // compare first len characters of term to substr

        if (cmp < 0){
            left = mid + 1;
        } else if (cmp > 0){
            right = mid - 1;
        } else {
            result = mid;
            left = mid + 1;
        }
    }
    return result;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int higher_match = highest_match(terms, nterms, substr);
    int lower_match = lowest_match(terms, nterms, substr);

    if (higher_match < 0 || lower_match < 0 || lower_match > higher_match){
        *n_answer = 0;
        *answer = NULL;
        return;
    }

    *n_answer = higher_match - lower_match + 1;
    *answer = (term *)malloc(sizeof(term) * (*n_answer));
    int count = 0;

    for (int i = lower_match; i <= higher_match; i++){
        strcpy((*answer)[count].term, terms[i].term);
        (*answer)[count].weight = terms[i].weight;
        count++;
    }
    qsort(*answer, *n_answer, sizeof(term), weightsort);    
}
