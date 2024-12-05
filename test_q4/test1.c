// segfault_array.c
#include <stdio.h>

int main() {
    int arr[4]; // Allocate an array of 500 integers
    int i=4;
    
    arr[50000] = i; // Out-of-bounds access 
    
    return 0;
}
