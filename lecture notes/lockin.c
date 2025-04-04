#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// When function returns, the stack memory used by arr is reclaimed so they don't exist afterwards
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
    int* data = func(); // we just assigned the pointer returned from func into data which HAS to be of type int* to store a pointer
    printf("%d\n", data[0]);
    free(data);  // free the memory we allocated 
}

// Note we used type int* for func() because malloc returns a pointer
// int cannot be used: this would be wrong because func() is declared to return an int, but arr is an int*


// Block of Structs (can also create blocks for structs w/ malloc)
student* students_block = (student *)malloc(sizeof(student)*500)

// ------------------------------------------------------------------

// Dealing with strings

// you can store a string as character array

char s1[] = "hi"; // same as char s1[] = {'h', 'i', '\0'}; // note: modifiable but cannot be reassigned

char s3[5]; // create array with enough space to hold "hi" (including null)
strcpy(s3, s1); // copies the string from s1 to s3

// if "hi" is stored at addresses 1032, 1033, 1034
// the address of the 'h' is 1032, and s1 gets converted to 1032 when used

char* s2 = 0; 
s2 = s1; // // legal, but strings are now aliases // s2 becomes 1032 when used (points to address of first element)

strcpy(s2, s1); // not yet OK, cannot copy address since s2 does not have enough space as defined pointer to NULL
                // same as s2[0] = s1[0], s2[1] = s1[1], ...

s2 = (char*)malloc(sizeof(char)*strlen(s1)+1); // allocate space
                                               // note: we want to strcpy from s1 to s2
                                               // multiply by strlen(s1) = # of non-null characters in s1, then +1 for NULL for strings
                                               // cast as char* since s2 is a pointer of char*

strcpy(s2, s1); // copy the contents of s1 into s2 (s2 has enough space now)

// ---------------------------------------------------------------------

// Pointers to pointers

void set_to_0(int** p_p_a){
    *p_p_a = 0  // update p_a to 0
}

int main(){
    int a = 5;
    int* p_a = &a;
    set_to_0(&p_a);     // p_a is now 0. a is not effected! (*p_p_a = value at address which is p_a)
}

// ---------------------------------------------------------------------

// string in structs

struct student1{
    char* name; // we store the address of where name is stored
}

// need to allocate name for each student using malloc & free

struct student2{
    char name[200]; // we store 200 charactesr
}

// don't need to allocate name for each student (200 characters are already defined/stored)

// Example:

typedef struct student1{
    char* name;
    double gpa;
} student1;

typedef struct student2{
    char name[200];
    double gpa;
} student2; 

student1 make_student1(char* name, double gpa){
    student1 s1;
    s1.name = name; // copying name into s1.name
    s1.gpa = gpa;   // copying gpa into s1.gpa
    return s1; 
}

student1 make_student1_new(char* name, double gpa){
    // create a new block of memory to store the name
    // store the address of the block at s1.name
    // copy name to the address s1.name (which you can modify)
   
    student1 s1;
    s1.name = (char *)malloc(sizeof(char)*strlen(name)+1); // use malloc to create enough space for s1.name
                                                           // name is now address of a block, which you CAN modify
    strcpy(s1.name, name);  // copy name into s1.name after we made enough space
    s1.gpa = gpa;
    return s1; 
}

student2 make_student2(char* name, double gpa){

    student2 s2;
    strcpy(s2.name, name); // copy name into s2.name // we cannot reassign to array, but we can copy arrays (if enough space)
    s2.gpa = gpa;
    return s2; 

    // SIDE NOTE: strcpy is equivalent to:
    for (int i = 0; i < strlen(s2.name)+1; i++){
        s2.name[i] = name[i]; // iterate through len of name, copy each element till the end (including NULL) into s2.name
    }

    //SIDE NOTE: strlen is equivalent to:
    size_t my_strlen(const char* str){   
        size_t len = 0;
        while (str[len] != '\0'){
            len++;
        }
        return len;
    }
}
 
int main(){
    student1 s1_const = {"Mike", 3.7}; // Directly initalize the struct (dont need a make_student1 function since read-only)

    student1 s1 = make_student1("Mike", 3.7);
    // cannot do:
    // s1.name[0] = "m"; // cannot do: "Mike" is read only

    student1 s1_new = make_student1_new("Mike", 3.7);
    s1_new.name[0] = 'm'; // can do: s1.name is now address of a block, which you CAN modify

    printf("Name: %s\n", s1_new.name);

    // Don't forget to free the allocated memory
    free(s1_new.name);

    return 0;
}

// ---------------------------------------------------------------------

// BLOCK OF STRUCTS

typedef struct student{
    char name[200];
    double gpa;
} student;

typedef struct student2{
    char* name;
    double gpa;
} student2;

student2* make_student2_block(int n){
    student2* students = (student2 *)malloc(sizeof(student2)*n);
    if (int i = 0; i < n; i++){
        students[i].name = (char *)malloc(sizeof(char)*200);
    }
    return students;
}

void destory_students(student2* students, int n){
    if (int i = 0; i < n; i++){
        free(students[i].name); // if I allocated every name, I first to need to free every name, then free the block
    }
    free(students);
}

int main(){
    student s1 = {"Mike", 4.8};     // Directly initalize a student struct
    student students[200];  // Create an array of 200 student structs
    strcpy(students[5].name, "Bob"); // Copy the string "Bob" into the name field of the 6th student (has 200 characters, so we can copy strings into it)

    student2 student2s[200];
    // strcpy(student2s[5].name, "Bob"); // Error! Cannot copy string into a pointer that has not been allocated

    // note the stuff on bottom is annoying because we have to allocate memory for each student2.name
    // we can use a block of structs to avoid this (refer to student2* make_student2_block(int n) function)
    student2s[5].name = (char *)malloc(sizeof(char)*200);
    strcpy(student2s[5].name, "Bob");
    free(student2s[5].name);

    
    // Free the allocated memory
    destroy_students(student2s, 200);
    return 0;
}

// ---------------------------------------------------------------------

// REALLOC


// ----------------------------------------------------------------------

// UNDERSTANDING LINKED LISTS

// Low Level Linked List Implementation

// if the data is 5, 10, 2
// it will be stored as:

// Example of implementation:
// 1000 next 3000
// 1020 data 5
// 2000 next NULL
// 2020 data 2
// 3000 next 2000
// 3020 data 10
// 5->10->2

// Linked List starts at 1000
// Linked List ends at the node for next = NULL


// NOTE: We cannot dynamically add an element to an existing array as there could not be space there
// The only option would be to re-allocate everything to a new location with enough space
// This is inefficient, especially for larger arrays
// HERE IS WHERE LINKED LISTS COME THROUGH:

// A list is an ordered collection of data items that supports the following operations:
// Insert(list, i, x): insert x at position i in the list
// Remove(list, i): remove the element at position i in the list
// Get(list, i): return the element at position i in the list

// A linked list consists of a data structure called a node, which consists of the following information
// data: the actual data you need to store
// next: the address of the next node

// ---------------------------------------------------------------------

// qsort (Include <stdlib.h> to use qsort)

// qsort provides a generic way to sort arryas
// Can sort any type of data IFF correct size and comparison function is provided

void qsort(void* base, size_t num, size_t size, int (*compar)(const void *, const void *));

// base: pointer to the first element of the array
// num: number of elements in the array
// size: size of each element in the array
// compar: Pointer to a function that compares two elements (to determine their order)

// 1. Prepare Your Data: whether you have an array of integers, floats, or structs, you must know the size of each element
int arr[] = {5, 2, 10, 1, 3};
int n = sizeof(arr)/sizeof(arr[0]);

// 2. Write a Comparison Function
// The function takes two const void* pointers and returns:
// A negative value if the first element is less than the second
// Zero if they are equal
// A positive value if the first element is greater than the second element

// EXAMPLE OF IMPLEMENTATION:

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// OR USE THIS COMPARE FUNCTION FOR INTEGERS, DOESN'T MATTER
int compareInts(const void *a, const void *b) {
    int intA = *(const int *)a;
    int intB = *(const int *)b;
    return (intA > intB) - (intA < intB);
}

int main(void) {
    int arr[] = { 3, 1, 4, 1, 5, 9, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), cmp);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// EXPECTED OUTPUT: 1 1 2 3 4 5 9

// ---------------------------------------------------------------------

// strcat:

// strcat concatenates two strings
// The first string must have enough space to store the second string

// EXAMPLE OF IMPLEMENTATION:

char dest[20] = "hello";
char src[] = "world";
strcat(dest, src);
printf("%s\n", dest); // Output: helloworld

// ---------------------------------------------------------------------

// strcmp:

// strcmp compares two strings lexicographically (alphabetically)
// Returns a negative value if the first string is less than the second
// Returns zero if the strings are equal
// Returns a positive value if the first string is greater than the second

// good to use as C doesn't have a proper way to compare strings (no == operator)

// EXAMPLE OF IMPLEMENTATION:

int main() {
    char password[] = "secure123";
    char input[20];

    printf("Enter password: ");
    scanf("%s", input);

    if (strcmp(password, input) == 0) {
        printf("Access Granted!\n");
    } else {
        printf("Access Denied!\n");
    }

    return 0;
}

// ---------------------------------------------------------------------

// atoi

// atoi converts a string to an integer
// Returns 0 if the string is not a valid integer

// EXAMPLE OF IMPLEMENTATION:

int main() {
    char str[] = "123";
    int num = atoi(str);
    printf("%d\n", num); // Output: 123

    return 0;
}

// ------------------------------


