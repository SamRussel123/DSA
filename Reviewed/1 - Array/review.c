#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int set[MAX];
    int size;
} Set;

// Function prototypes
void insertToSet(Set *S, int data);
void deleteFromSet(Set *S, int data);
void populateSet(Set *S);
void printSet(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    printf("\033[H\033[J"); // Clear screen

    Set A = {{}, 0};
    Set B = {{}, 0};

    populateSet(&A);
    populateSet(&B);

    printf("Set A: ");
    printSet(A);

    printf("Set B: ");
    printSet(B);

    Set U = Union(A, B);
    printf("\nUnion: ");
    printSet(U);

    Set I = Intersection(A, B);
    printf("Intersection: ");
    printSet(I);

    Set D = Difference(A, B);
    printf("(A - B): ");
    printSet(D);

    D = Difference(B, A);
    printf("(B - A): ");
    printSet(D);

    int temp;
    printf("\nRemove an element from set A: ");
    scanf(" %d", &temp);

    deleteFromSet(&A, temp);
    printf("A without '%d': ", temp);
    printSet(A);

    return 0;
}

// =======================
// FUNCTION DEFINITIONS
// =======================

void insertToSet(Set *S, int data) {
    // TODO: Write your logic for inserting data into the set (no duplicates)
   if(S->size < MAX){
        int i;
        for(i = 0; i < S->size && S->set[i] != data; ++i){}

        if(i == S->size){
            S->set[S->size++] = data;
        }
   }
}


void deleteFromSet(Set *S, int data) {
    // TODO: Write your logic for deleting data from the set
   if(S->size > 0){
        int i;
        for(i = 0; i < S->size && S->set[i] != data; ++i) {}

        if(i != S->size){
            S->size--;

            if(S->size > 0){
            S->set[i] = S->set[S->size];
        }
     }
   }
}

void populateSet(Set *S) {
    // TODO: Prompt user to input numbers until S->size reaches MAX/2
    printf("Enter a number\n");

    for(; S->size < MAX / 2 ;){
        int data;
        printf("Enter number %d: ", S->size);
        scanf("%d", &data);
        insertToSet(S, data);
    }

    printf("\n");
}

void printSet(Set S) {
    // TODO: Print all elements in the set
    for(int i = 0; i < S.size; ++i){
        printf("%d", S.set[i]);
    }

    printf("\n");

}

Set Union(Set A, Set B) {
    // TODO: Return a new set containing all elements from A and B (no duplicates)
    Set S = A;

    int i; 
    for(i = 0; i < B.size; ++i){
        int j; 
        for(j = 0; j < S.size && B.set[i] != S.set[j]; ++j) {}

        if(j == B.size){
            S.set[S.size++] = B.set[i];
        }
    }

    return S;
}

Set Intersection(Set A, Set B) {
    // TODO: Return a new set containing only common elements between A and B
    Set S = {{}, 0};

    int i;
    for(i = 0; i < A.size; ++i){
        int j;
        for(j = 0; j < B.size && A.set[i] != B.set[j]; ++j){}

        if(j != B.size){
            S.set[S.size++] = A.set[i];
        }
    }

    return S;
}

Set Difference(Set A, Set B) {
    // TODO: Return a new set containing elements in A that are not in B
    Set S = {{}, 0};

    int i;
    for(i = 0; i < A.size; ++i){
        int j;
        for(j = 0; j < B.size && A.set[i] != B.set[j]; ++j){}

        if(j == B.size){
            S.set[S.size++] = A.set[i];
        }
    }

    return S;
}