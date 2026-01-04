#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

// Min-Heap (Partially Ordered Tree)
// Parent is always <= its children
typedef struct {
    int elements[MAX];
    int lastIndex;     // index of the last filled position
} MinHeap;

void initTree(MinHeap *T);
void populateTree(MinHeap *T, int arr[], int size);
void insertTree(MinHeap *T, int data);
int deleteMin(MinHeap *T);
void displayTree(MinHeap T);

int main() {
    MinHeap T;
    int arr[] = {4, 2, 5, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);              // start with empty heap
    populateTree(&T, arr, size); // insert all elements

    printf("Elements in order: ");
    displayTree(T);             // print in sorted order

    return 0;
}

void initTree(MinHeap *T) {
    T->lastIndex = -1;          // empty heap indicator
}

void populateTree(MinHeap *T, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        insertTree(T, arr[i]);  // insert elements one by one
    }
}

void insertTree(MinHeap *T, int data) {
    // Make sure there is space in the heap
    if(T->lastIndex + 1 < MAX) {

        int child = ++T->lastIndex;       // place new element at end
        int parent = (child - 1) / 2;     // compute parent index

        // Bubble-up: move parent down if it's bigger than new data
        while(child > 0 && T->elements[parent] > data) {

            T->elements[child] = T->elements[parent]; // shift parent down

            child = parent;           // move upward
            parent = (parent - 1) / 2;
        }

        T->elements[child] = data;    // place data in correct location
    }
}

int deleteMin(MinHeap *T) {
    int temp = -1;

    // Only delete if there are elements
    if(T->lastIndex >= 0) {
        temp = T->elements[0];       // minimum element = root

        // Take last element; heap size decreases by 1
        int data = T->elements[T->lastIndex--];

        int parent = 0;              // start bubbling down from the root
        int LC = parent * 2 + 1;     // left child index
        int RC = LC + 1;             // right child index

        // Choose the smaller child (higher priority in Min-Heap)
        int child = T->elements[LC] < T->elements[RC] ? LC : RC;

        // Bubble-down: while child is in range and smaller than data
        while(child <= T->lastIndex && T->elements[child] < data) {

            T->elements[parent] = T->elements[child]; // move child up

            parent = child;          // move down to child
            LC = parent * 2 + 1;
            RC = LC + 1;

            // again pick the smaller child
            child = T->elements[LC] < T->elements[RC] ? LC : RC;
        }

        T->elements[parent] = data;  // place last element properly
    }

    return temp;                     // return deleted minimum
}

void displayTree(MinHeap T) {
    int temp;

    // Continuously delete the minimum until heap is empty
    while((temp = deleteMin(&T)) != -1) {
        printf("%d ", temp);
    }
}