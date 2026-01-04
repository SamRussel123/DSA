#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

// prioritized by elements
typedef struct {
    int elements[MAX];
    int lastIndex;
} MaxHeap;

void initTree(MaxHeap *T);
void populateTree(MaxHeap *T, int arr[], int size);
void insertTree(MaxHeap *T, int data);
int deleteMax(MaxHeap *T);
void displayTree(MaxHeap T);

int main() {
    MaxHeap T;
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    printf("Elements in order: ");
    displayTree(T);

    return 0;
}

void initTree(MaxHeap *T) {
    T->lastIndex = -1;
}

void populateTree(MaxHeap *T, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        insertTree(T, arr[i]);
    }
}

void insertTree(MaxHeap *T, int data) {
    if(T->lastIndex + 1 < MAX) {
        int child = ++T->lastIndex;
        int parent = (child - 1) / 2;

        while(child > 0 && T->elements[parent] < data) {
            // shift
            T->elements[child] = T->elements[parent];

            child = parent;
            parent = (parent - 1) / 2;
        }

        T->elements[child] = data;
    }
}

int deleteMax(MaxHeap *T) {
    int temp = -1;

    if(T->lastIndex >= 0) {

        temp = T->elements[0];                     // max element
        int data = T->elements[T->lastIndex--];    // last element

        int parent = 0;
        int LC = parent * 2 + 1;                   // left child index
        int RC = LC + 1;                           // right child index

        // pick bigger child (only valid if both children exist)
        int child = (RC <= T->lastIndex)
                    ? (T->elements[LC] > T->elements[RC] ? LC : RC)
                    : LC;   // if RC does not exist, pick LC

        // bubble down
        while(child <= T->lastIndex && T->elements[child] > data) {

            T->elements[parent] = T->elements[child];   // move child up

            parent = child;       // move down the heap
            LC = parent * 2 + 1;
            RC = LC + 1;

            // choose bigger child again using ternary
            child = (LC <= T->lastIndex) ?
                        ((RC <= T->lastIndex)
                            ? (T->elements[LC] > T->elements[RC] ? LC : RC)
                            : LC)
                        : T->lastIndex + 1;   // no children → force exit
        }

        T->elements[parent] = data;   // put data in correct location
    }

    return temp;
}

void displayTree(MaxHeap T) {
    int temp;
    while((temp = deleteMax(&T)) != -1) {
        printf("%d ", temp);
    }
}