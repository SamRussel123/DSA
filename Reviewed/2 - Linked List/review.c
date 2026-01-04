#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} *Set;

// Function prototypes
void populateSet(Set *S);
void insert(Set *S, int data);
void printSet(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    printf("\033[H\033[J"); // Clear screen

    Set A = NULL;
    Set B = NULL;

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

    return 0;
}

// =======================
// FUNCTION DEFINITIONS
// =======================

void populateSet(Set *S) {
    // TODO: Ask user for size
    int size = 0;
    printf("Enter number: ");
    scanf("%d", &size);

    // TODO: Loop to get inputs and call insert(S, data)
    for(int i = 0; i < size; ++i){
        int data;
        printf("Enter element i: %d", i);
        scanf("%d", &data);
        insert(S, data);
    }
    

    printf("\n");
}

void insert(Set *S, int data) {
    // TODO: Traverse until end or duplicate found
    Set *trav = S;

    for(; *trav != NULL && (*trav)->data != data; trav = &(*trav)->next) {}
    
    // TODO: If not found, allocate new node and link
    if(*trav == NULL){
        Set temp = malloc(sizeof(Set));

        if(temp != NULL){
            temp->data = data;
            temp->next = NULL;
            *trav = temp;
        }
    }
    
}

void printSet(Set S) {
    // TODO: Traverse the linked list and print each data value
    for(Set curr = S; curr != NULL; curr = curr->next){
        printf("%d", curr->data);
    }
    printf("\n");
}

Set Union(Set A, Set B) {
    // TODO: Create a new list U

    Set U = NULL;

    Set *trav = &U;
    
    // TODO: Copy all elements from A

    for(Set curr = A; curr != NULL; curr = curr->next){
        Set temp = malloc(sizeof(struct node));

        if(temp != NULL){
            temp->data = curr->data;
            *trav = temp;
            trav = &(*trav)->next;
        }
    }

    *trav = NULL;
    
    // TODO: Insert unique elements from B
    for(Set curr = B; curr != NULL; curr = curr->next) {
        insert(&U, curr->data);
    }

   
    Set U = NULL;
    return U;
}

Set Intersection(Set A, Set B) {
    // TODO: Create a new list I
    Set I = NULL;
    for(Set currA = A; currA != NULL; currA = currA->next){
        Set currB;
        for(currB = B; currB != NULL && currA->data != currB->data; currB = currB->next) {}

        if(currB != NULL){
            Set temp = malloc(sizeof(struct node));
            if(temp != NULL){
                temp->data = currA->data;
                temp->next = I;
                I = temp;
            }
        }
    }
    // TODO: Add elements that exist in both A and B
    
    return I;
}

Set Difference(Set A, Set B) {
    // TODO: Create a new list D

    Set D = NULL;
    for(Set currA = A; currA != NULL; currA = currA->next){
        Set currB;
        for(currB = B; currB != NULL && currA->data != currB->data; currB = currB->next) {}

        if(currB == NULL){
            Set temp = malloc(sizeof(struct node));
            if(temp != NULL){
                temp->data = currA->data;
                temp->next = D;
                D = temp;
            }
        }
    }
    
    
    // TODO: Add elements that exist in A but not in B
    Set D = NULL;
    return D;
}