#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Question 1
void set_even_to_zero(int* block, int size) {
    for (int i = 0; i < size; i+=2){
        block[i] = 0;
    }
}  

// Question 2
void strcat_v1(char* dest, const char* src){
    while (*dest != '\0'){
        dest++;
    }
    while (*src != '\0'){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void strcat_v2(char dest[], const char src[]){
    int i = 0;
    int j = 0;
    while (dest[i] != '\0'){
        i++;
    }
    while (src[j] != '\0'){
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

// Question 3
int my_strcmp_rec(char* s1, char* s2){
    if (*s1 == '\0' && *s2 == '\0'){
        return 0;
    }
    if (*s1 > *s2){
        return 1;
    }
    if (*s1 < *s2){
        return -1;
    }
    return my_strcmp_rec(s1+1, s2+1);   
}

// Question 4
int binary_search_left(int* arr, int size, int target) {    // First occurence of target in arr
    int left = 0;
    int right = size - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid; // Record the position
            right = mid - 1; // Continue searching in the left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int binary_search_right(int* arr, int size, int target) {   // Last occurence of target in arr
    int left = 0;
    int right = size - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid; // Record the position
            left = mid + 1; // Continue searching in the right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Question 5 (wrong, I think)
int my_atoi(char* str){
    for (int i = 0; i < size2; i++){
        if (*str != isdigit){
            *str -'0';                    // convert the element to digit logic
            str += sizeof(int);             // or size of char?
        }
    return *str; 
    }
}

// apparently this is the correct implementation
int my_atoi(char* str){
    int result = 0;
    for (int i = 0; i < strlen(str); i++){
        if (isdigit((unsigned char)str[i])){
            result = result * 10 + (str[i] - '0');
        }
    }
   return result;
}

int main() {
    int block[] = {5, 6, 7, 8};
    int size = 4;
    set_even_to_zero(block, size);

    // to print the updated array
    printf("{");
    for (int i = 0; i < size; i++){
        if (i != 0) {
            printf(", ");
        }
        printf("%d", block[i]);
    }
    printf("}");

    // ----------------------------

    char dest1[100] = "good";
    char src1[] = "morning";
    strcat_v2(dest1, src1);
    printf("%s\n", dest1);

    char dest2[100] = "good";
    char src2[] = "morning";
    strcat_v2(dest2, src2);
    printf("%s\n", dest2);

    // -------------------------------

    char s1[] = "shi";
    char s2[] = "fhi";
    printf("%d\n", my_strcmp_rec(s1, s2));
    return 0;

    // -------------------------------

    char str[] = "abc";
    int size2 = 4;
}  
