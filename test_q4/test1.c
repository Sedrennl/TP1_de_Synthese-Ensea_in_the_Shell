//TP Synthese ENSEA in the Shell
//Program test-Segmentation fault for question 4
//BLARET julien and LABROUSSE Sédrenn on 05/12/24.
//

#include <stdio.h>

int main() {
    int arr[4]; // Allocate an array of 4 integers
    int i=4;
    
    arr[50000] = i; // Out-of-bounds access 
    
    return 0;
}
