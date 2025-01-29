#include <stdio.h>
#include <stdlib.h>

void change_int(int* p_x){
    *p_x = 123;
}

void create_str(char **p_str){
    *p_str = (char*)malloc(sz * sizeof(char));
    if(*p_str == NULL){
        printf("ERROR: out of memory, download more RAM LMFAO");
        exit(1);
    }
}

int main(){
    char* str;
    create_str(&str, 200); // make str be the address of the first element
    strcpy(str, "Mike");
}