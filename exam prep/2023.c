#include <stdio.h> 
#include <stdlib.h>

// Q1 (time complexity: O(n))
double fact(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }

    if (n < 0) {
        return -1;
    }
    
    return n * fact(n-1);
}

// Q2:


// Q3:
int compare_arr(int* arr1, int* arr2, int len1, int len2)
{
    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0 && len2 == 0) {
        return 1;
    }

    if (arr1[0] != arr2[0]) {
        return 0;
    }

    return compare_arr(arr1 + 1, arr2 + 1, len1 - 1, len2 - 1);
}

int main() {
    int arr1[] = {7, 8, 9};
    int arr2[] = {7, 8, 9};
    int arr3[] = {7, 8};

    if (compare_arr(arr1, arr2, 3, 3)) {
        printf("%s\n", "arr1 and arr 2 are equal");
    }

    else {
        printf("%s\n", "arr1 and arr2 are not equal");
    }

}

// Q4




