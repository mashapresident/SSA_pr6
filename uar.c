#include <stdio.h>

int* foo() {
    int local_var = 42; 
    return &local_var; 
}

int main() {
    int* ptr = foo(); 
    printf("%d\n", *ptr); 
    return (*ptr == 42);
}