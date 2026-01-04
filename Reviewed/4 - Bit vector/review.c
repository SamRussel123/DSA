#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef int Set[MAX]; // only ones and zeroes

// Function prototypes
void populateSet(Set S);
void printSet(Set S);
Set *Union(Set A, Set B);
Set *Intersection(Set A, Set B);
Set *Difference(Set A, Set B);

int main() {
    printf("\033[H\033[J"); // Clear screen

    Set A = {};
    Set B = {};

    populateSet(A);
    populateSet(B);

    printf("Set A: ");
    printSet(A);

    printf("Set B: ");
    printSet(B);

    Set *U = Union(A, B);
    printf("\nUnion: ");
    printSet(*U);

    Set *I = Intersection(A, B);
    printf("Intersection: ");
    printSet(*I);

    Set *D = Difference(A, B);
    printf("(A - B): ");
    printSet(*D);

    D = Difference(B, A);
    printf("(B - A): ");
    printSet(*D);

    return 0;
}

// ===========================
// FUNCTION DEFINITIONS
// ===========================

void populateSet(Set S) {
    // TODO: Ask user to input values
    for(int i = 0; i < MAX; ++i){
        int data;
        printf("Enter element %i: ", i);
        scanf("%d", &data);

        if(data >= 0 && data < MAX){
            S[data] = 1;
        }
    }
    // TODO: Mark elements in S as 1 for entered indices
}

void printSet(Set S) {
    // TODO: Loop through indices and print elements that are 1
    for(int i = 0; i < MAX; ++i){
        if(S[i] == 1){
            printf("%d ", i);
        }
    }
    printf("\n");
}

Set *Union(Set A, Set B) {
    // TODO: Allocate memory for a new Set
    Set *S = malloc(sizeof(Set));
    
    // TODO: Use bitwise OR (|) to combine A and B
    if(S != NULL){
        for(int i = 0; i < MAX; ++i){
            (*S)[i] = A[i] | B[i];
        }
    }
    
    return S;
}

Set *Intersection(Set A, Set B) {
    // TODO: Allocate memory for a new Set
    Set *S = malloc(sizeof(Set));

        // TODO: Use bitwise AND (&) to keep only common elements
    if(S != NULL){
        for(int i = 0; i < MAX; ++i){
        (*S)[i] = A[i] & B[i];
        }
    }

    return S;
}

Set *Difference(Set A, Set B) {
    // TODO: Allocate memory for a new Set
    Set *S = malloc(sizeof(Set));
    
    // TODO: Use bitwise AND (&) and NOT (~) to subtract B from A
    
    if(S != NULL){
        for(int i = 0; i < MAX; ++i){
        (*S)[i] = A[i] & (~B[i]);
        }
    }
    
    return S;
}