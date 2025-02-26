#include <stdio.h>

//Want: what is the length of the string starting at 1032?
// ANSWER: 1 + [length of the string starting at 1033]

int my_strlen(char* s) {
    int cur_i = 0;
    while(s[cur_i] != '\0'){
        cur_i++; // same as cur_i += 1
    }
    return cur_i;
}

// WANT: recursive my_strlen (do this recursively as compared to while loop)
// base case: if s[0] is '\0', can return 0
// recursive step: 1 + my_strlen(s + 1)

int my_strlen_rec(char *s)
{
    if(s[0] == '\0') {
        return 0;
    }
    else {
        return 1 + my_strlen_rec(s+1);
    }
}

int main() {

    char s[] = "abc";
    printf("%d\n", my_strlen(s));
}