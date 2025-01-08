#include <stdio.h>

int main() {

    int a = 42;
    long int la = 21383281828L; // any 64 bit integer
    char c = '@'; // character: a single character. Note: we cannot do *c as c is not an address 
    char* s = "abs"; // "string": the address of a first character in the sequence 'a', 'b', 's', '\0'
    char* p_c = &c; // & called the ampersand means "address of"
    return 0;
}

// the stack is the frame of the current local variables 
// the heap goes into depth on a section of the variable in the stack
// abs needs to be stored somewhere, C stores the value of the address in a heap from the stack of s
