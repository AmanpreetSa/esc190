#include <stdio.h>

char c = 'a'; // a single character 
char* lc = "abacada"; // "string" the address of the first character in the sequence

int arr[] = {5, 10, 2}; // can only use braces during initalization
arr[0] = 3;

int arr_2[10]; // an array with size 10

for (int i = 0; i < 10; i++){
    arr_2[i] = i;
} //only way to fill defined array AFTER initalization is using loops or manually arr_2[0] = ..., arr_2[1] = ..., etc.


int arr[3] = {1, 2, 3}; // pre-determined size of 3, if elements less than 3, then rest are filled with 0 (useful if you know how much to fill array but don't need to fill it during initalization)
int arr[] = {1, 2, 3}; 

// arrays points to the address of the first element; use  pointer arithmetic to get other elements






