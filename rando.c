#include <stdio.h>
#include <stdlib.h>

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
// a[0] = *(a+0) are equivalent


int f(int* p_a){
    *p_a = 43
} // function f takes in a pointer (address) and dereferences it to 43


int a = 42;
char* s = "xyz";
int arr[] = {4, 5};
int* p_a = &a;

// char* means a value of type "address of char"
// Array & string elements are stored in consecutive cells in memory
// s is the address where 'x' is stored
// arr gets converted into the address of where 4 is stored
// &a is the address where a is stored
// *p_a is the value at address p_a (dereferencing)
// *arr is the value at address arr (same as arr[0])


void f(int a){
    a = 42;
}
// f(43) copies 43 to a local variable a. The variable a is local, so f has no effect

void f(int* p_a){
    p_a = 0;
}

int a = 45;
// f(&a) copies &a to local variable p_a. The variable p_a is local, so f has no effect.

void f(int* p_a){
    *p_a = 55
}
// f(&a) copies &a to local variable p_a. The variable p_a is local, but *p_a is the same as 'a', so f DOES have an effect. 


// Summary
// p_a+i is the address i slots after p_a
// *(p_a+i) is the same as p_a[i]: the contents i slots after p_a
// arrays int arr[] gets converted tp &(arr[0]) when used

// ------------------------------------------------


// C does not have strings

char s1[] = "abc"; 
// an array of type char with characters 'a', 'b', 'c', '\0'
// shorthand char s1[] = {'a', 'b', 'c', '\0'}
// fixed memory size & cannot be reassigned
// You can change the contents (e.g. s1[0] = 'x') 

char* s2 = "abc";
// put the block 'a', 'b', 'c', '\0' somewhere in memory
// s2 is the address of where a is stored

// Difference: an array is generally a local variable, only exists while the function is running. 
// s2 stores the address of a memory block that will persist in memory


// Arrays char s1[]) and pointers (char* s2) 
// An array is a fixed memory block with a constant address, so while its contents can be modified (s1[0] = 'X';), its base address cannot be reassigned (s1 = "xyz"; is invalid). 
// In contrast, a pointer stores a memory address that can be changed (s2 = "xyz"; is valid),  but if it points to a string literal, modifying its contents (s2[0] = 'X';) leads to undefined behavior. 
// Arrays decay into pointers in some contexts, but their base addresses remain fixed, making reassignment impossible.

// Arrays allocate and store all elements in consecutive memory cells
// Pointers only store an address and do not allocate space for elements.
// Arrays "act like" pointers in expressions and function calls, but remain fixed in memory


// the literal "abc" is actually of type const char *
// not allowed to modify but can convert to char * 

char* str = "hello";
str = "world";  // ✅ Allowed
str[0] = 'H';   // ❌ Undefined behavior (read-only memory modification)

char* const str = "hello";
str = "world";  // ❌ Error! Pointer cannot be changed
str[0] = 'H';   // ❌ Undefined behavior (same issue as above)

// In general, const is used if we know something doesn't modify, we tell the compiiler so we don't modify by mistake
// const helps to prevent undefined behaviour if we know something DOESN'T change (solidfy it to not risk crashing program)


// -------------------------------------------------


typedef int arr_sz_t;   // creates a new type name arr_sz_t that is equivalent to int
arr_sz_t sz_of_arr = 15;    // same as int sz_of_arr = 15;

// useful since if we find out int is actually too small for array sizes, then we can just to:

typedef unsigned long int arr_sz_t;

// instead of manually changing every int


// --------------------------------------------------

// Compound Data Strutures: want to store several values that relate to the same subject

struct student{
    char name[200]; // in structs, we must predefine value for array  (compiler does not allow an unsized array inside a struct because it doesn’t know how much memory to allocate)
    char number[11];
    double GPA;
};

int main(){
    // access the fields of the struct using
    struct student s1 = {"John Doe", "1234567890", 3.3};
    printf("%s\n %f\n", s1.name, s1.GPA);
}

// use typedef to avoid having to repeat "struct"

typedef struct student{
    char name[200];
    char number[11];
    double GPA;
} student;

int main(){
    student s1 = {"John Doe", "1234567890", 3.3};
    printf("%s\n %f\n", s1.name, s1.GPA);
}

// -------------------------------------------------

// Using Pointers to structs allows for more efficiency than directly copying entire struct to access value

typedef struct student{
    char name[200];
    char number[11];
    double GPA;
} student;

int main(){
    student s1 = {"John Doe", "1234567890", 3.3};
    student* p_s1 = &s1;
    printf("%s\n %f\n", (*p_s1).name, (*p_s1).GPA);

    // OR

    printf("%s\n %f\n", p_s1->name, p_s1->GPA);
}

// ------------------------------------------------

// malloc
// local arrays disappear once a function is done running
// arrays in C are not resizable
// malloc allocates space in the memory table to store a block of values

int* block_int = (int*)malloc(sizeof(int) * 150) // allocate space for 150 integers 
                                                 // malloc returns the address of element 0 (void* is generic pointer)
                                                 // (int*) casts the pointer to int* so we can use it as an array of integers

block_int[7] = 42;
*(block_int + 7) = 42; // block_int + 7 gets to right location in memory table since C knows how many cells ints take up

// --------------------------------------------------

// sizeof works differently for pointers and arrays 

int arr[] = {1, 2, 3};
sizeof(arr)/sizeof(arr[0]);  // Gives the length of the array


void sz(int* a)  // Same as void sz(int a[])
{
    sizeof(a);  // 8 (or 4 on 32-bit)
}

int main(){
    int a[] = {1, 2, 3};
    sz(a);
}

// Array decays to pointer when passed to function
// a is not an array inside sz, it's just a pointer and sizeof(a); returns 8 as that's the size of a pointer of int*


// How to PROPERLY pass an array and keep the size:

void sz(int* a, int length)
{
    printf("Size of array: %d\n", length);
}

int main()
{
    int a[] = {1, 2, 3};
    sz(a, sizeof(a) / sizeof(a[0]));  // ✅ Pass actual array size
}

// --------------------------------------------------

// Difference between local arrays and dynamically allocated memory (memory blocks) in functions.

// When function returns, the stakc memory used by arr is reclaimed so they don't exist afterwards
int* func() {
    int arr[3] = {1, 2, 3};  // ⚠️ Local array (stack memory)
    return arr;  // ⚠️ Undefined behavior!
}

// Better alternative is using Dynamically Allocated Memory through malloc

int* func() {
    int* arr = (int *)malloc(sizeof(int) * 3);  // ✅ Allocated on the heap
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    return arr;  // ✅ Safe to return
}

int main() {
    int *data = func();
    printf("%d\n", data[0]);  // ✅ Works fine
    free(data);  // ✅ Don't forget to free the memory
}

// Note we used type int* for func() because malloc returns a pointer
// Int cannot be used: this would be wrong because func() is declared to return an int, but arr is an int*
