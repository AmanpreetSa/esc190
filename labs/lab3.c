#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct student1{
    char name[200];
    char student_number[11];
    int year;
} student1;

typedef struct student2{
    char *name;
    char *student_number;
    int year;
} student2;

void print_student(student1 s){
    printf("%s\n", s.name);
    printf("%s\n", s.student_number);
    printf("%d\n", s.year);
}

void set_default_name(student1 *p_s)
{
    strcpy(p_s->name, "Default Student");   // Access the value of the pointer at name (wherever struct name lies in), and copy "Default Student" into name
}

void set_default_name_wrong(student1 s)
{
    strcpy(s.name, "Default Solution"); // Modifies the copy, NOT the original struct
    s.year = 0; // Modifies the copy, NOT the original struct
}

void create_block1(student1 **p_p_s, int n_students)
{
    *p_p_s = (student1 *)malloc(sizeof(student1)*n_students);
}

void set_name(student1* p_s, const char* string)
{
    strncpy(p_s->name, string, 199);
    p_s->name[199] = '\0';
}

void destroy_block1(student1 *p_s)
{
    free(p_s);
}

void create_block2(student2 **p_p_s, int num_students)
{
    *p_p_s = (student2 *)malloc(sizeof(student2)*num_students);

    for (int i = 0; i < num_students; i++){
        (*p_p_s)[i].name = NULL;
        (*p_p_s)[i].student_number = NULL;
        (*p_p_s)[i].year = 0; 
    }
}

void set_name2(student2 *p_s, const char* new_name)
{
    p_s->name = (char *)malloc(sizeof(char)*(strlen(new_name)+1));
    strcpy(p_s->name, new_name);
}

void destory_block2(student2 *students, int num_students)
{
    for (int i = 0; i < num_students, i++){
        free(students[i].name);
        free(students[i].student_number);
    }
    free(students);
}

// This function takes in "test.txt", and prints the file's contents

int read_file() {
    FILE *fp = fopen("test.txt", "r"); 
    char line[200];  
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);  
    }
    fclose(fp);  
}

// Function reads line by line, computes average of integers (assuming one integer per line)

int average_integers_from_file(const char* filename)
{
    FILE *fp = fopen(filename, "r");
    char line[200];
    int res = 0;
    int average = 0;
    int count = 0;
    while(fgets(line, sizeof(line), fp)){
        res += atoi(line);
        count++;
    }
    fclose(fp);
    average = res/count;
    return average;
}

int main() {
    student1 s1;

    strcpy(s1.name, "John Doe");
    strcpy(s1.student_number, "1234567890");
    s1.year = 2;

    print_student(s1);
    set_default_name(%s1);
    set_default_name_wrong(s1); // receives a copy of s1, changes made inside the function only changes the copy

    student1* students;
    int n_students = 3;
    create_block1(&students, n_students);

    strcpy(students[0].name, "Alice");
    students[0].year = 2;
    strcpy(studnets[1].name, "Bob");
    students[1].year = 1;
    strcpy(studnets[2].name, "Charlie");
    students[2].year = 3;

    for (int i = 0; i < n_studnets; i++)
    {
        printf("Student %d: %s, Year: %d\n", i + 1, students[i].name, students[i].year);
    }

    student1 s1;
    const char* string = "Hello";
    set_name(&s1, string);

    destory_block(students)

    student2* students = NULL;
    int num_students = 3;
    create_block2(&students, num_students);

    student2 s2;
    set_name2(&s2, "Bob");
    printf("Student: %s\n", s2.name);

    destroy_block2(students, num_students);

    return 0;
}

// -------------------------------------------------------------------------------------

// Normally passing s (not a pointer) in a struct with fixed-size arrays will modify the COPY of the struct
// The only way to modify the original is passing a pointer

// For structs made out of a pointers, you can either pass in s (not a pointer, s.name) or pass in a pointer *s (s->name)
// and both will still modify the original struct

// Example from AI:

typedef struct student1 {
    char name[200];  // Fixed-size array
    char student_number[11];
    int year;
} student1;

typedef struct student2 {
    char *name;  // Pointer-based string
    char *student_number;
    int year;
} student2;

// ✅ Function that modifies student1 by VALUE (changes won't persist)
void modify_student1(student1 s) {
    strcpy(s.name, "Modified Name");
}

// ✅ Function that modifies student1 by REFERENCE (changes WILL persist)
void modify_student1_pointer(student1 *s) {
    strcpy(s->name, "Modified Name");
}

// ✅ Function that modifies student2 by VALUE (changes WILL persist since name is a pointer)
void modify_student2(student2 s) {
    strcpy(s.name, "Modified Name");  // Pointer remains the same, so changes persist
}

// ✅ Function that modifies student2 by REFERENCE (changes WILL persist)
void modify_student2_pointer(student2 *s) {
    strcpy(s->name, "Modified Name");
}