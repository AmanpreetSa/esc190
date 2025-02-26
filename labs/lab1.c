#include <stdio.h>
#include <stdbool.h>

// Question 2
void change(int* p_a) {
    *p_a = 11;
}

// Question 3
void change_arr(char arr[]){
    arr[1] = 'X';
    arr[2] = 'Y'; 
}

// Question 4
void insertion_sort(int *arr, int len){
    int i, j, key;
    for (i = 1; i < len; i++){
        key = arr[i];   // key is set to the current element you want to insert
        j = i - 1;  // j starts at i-1, which is the last index of the sorted portion—not the last element of the entire array
        while (j >= 0 && arr[j] > key){ 
            arr[j+1] = arr[j]; // elements greater than key are shifted right
            j = j - 1; // moves the index one position to the left (allows to keep checking the elements)
        }
        arr[j+1] = key; // once correct spot is found, key is inserted at arr[j+1]
    }
}

// Question 5
int len_of_string(char* str){
    int length = 0;
    while (str[length] != '\0'){
        length++;
    }
    return length;
}

// Question 6
void seq_replace(int* arr1, unsigned long arr1_sz, int* arr2, unsigned long arr2_sz) {
    for (int start = 0; start <= arr1_sz - arr2_sz; start++) {
        bool isSame = true;
        
        // Check if sequence matches
        for (int j = 0; j < arr2_sz; j++) { // Loop through each element of arr2 to compare with corresponding elements in arr1.
            if (arr1[start + j] != arr2[j]) {   // Check if current elements match. // We need [start + j] because +j helps us compare sequences of arr2 with arr1.
                isSame = false;
                break;  // Exit early once we know it's not a match
            }
        }
        
        // If sequence matches, replace with zeros
        if (isSame) {
            for (int x = 0; x < arr2_sz; x++) { // Loop through the length of arr2.
                arr1[start + x] = 0;    // Replace matched elements in arr1 with zeros.
            }
        }
    }
}

int main() {
    int a = 5;
    change(&a);
    printf("%d\n", a);

    char arr[100] = "Hello";
    change_arr(arr);
    printf("%s\n", arr);

    char b[] = "Hello";
    int string_length = len_of_string(b);
    printf("%d\n", string_length);

    printf("-----------------\n");

    int m[] = {5, 6, 7, 8, 6, 7};
    int n[] = {6, 7};
    seq_replace(m, 6, n, 2);
    for(int i = 0; i < 6; i++){
        printf("%d\n", m[i]);
    }
    return 0;
}
