#include <stdio.h>

int linear_search(int* a, int sz, int elem){
    int i;
    for (i = 0; i < sz; i++){
        if(a[i] == elem){
            return i;
        }
    }
    return -1;   // fall case if elem doesn't exist    
}

void reverse_arr(int *arr, int sz){
    int i;
    int temp;
    for (i = 0; i < sz/2; i++){ // only need to go half way when reversing
        temp = arr[i];
        arr[i] = arr[sz-1-i];
        arr[sz-1-i] = temp;
    }
}

int main(){
    printf("%s\n", "Hello World");

    int arr[] = {5, 6, 7, 8}; // Example array
    int sz = sizeof(arr) / sizeof(arr[0]); // Calculate array size

    printf("Original array: ");
    for (int i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Reverse the array
    reverse_arr(arr, sz);

    printf("Reversed array: ");
    for (int i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}