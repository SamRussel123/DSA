#include <stdio.h>
#define MAX 4

typedef struct {
    int elem, next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap *V, int index);
void insertFirst(List *L, VHeap *V, int elem);
void insertLast(List *L, VHeap *V, int elem);
void deleteElem(List *L, VHeap *V, int elem);
void display(List L, VHeap V);

void initialize(VHeap *V) {
    for (int i = 0; i < MAX - 1; i++) {
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
    V->avail = 0;
}

int allocSpace(VHeap *V) {
    int i = V->avail;
    if (i != -1) {
        V->avail = V->H[i].next;
    }
    return i;
}

void deallocSpace(VHeap *V, int i) {
    V->H[i].next = V->avail;
    V->avail = i;
}

void insertFirst(List *L, VHeap *V, int e) {
    int n = allocSpace(V);
    if (n != -1) {
        V->H[n].elem = e;
        V->H[n].next = *L;
        *L = n;
    } else {
        printf("Heap full\n");
    }
}

void insertLast(List *L, VHeap *V, int e) {
    int n = allocSpace(V);
    if (n != -1) {
        V->H[n].elem = e;
        V->H[n].next = -1;

        if (*L == -1) {
            *L = n;
        } else {
            int t = *L;
            while (V->H[t].next != -1) {
                t = V->H[t].next;
            }
            V->H[t].next = n;
        }
    } else {
        printf("Heap full\n");
    }
}

void deleteElem(List *L, VHeap *V, int e) {
    int *current = L;
    while (*current != -1 && V->H[*current].elem != e) {
        current = &V->H[*current].next;
    }
    if (*current != -1) {
        int delNode = *current;
        *current = V->H[delNode].next;
        deallocSpace(V, delNode);
    } else {
        printf("Not found\n");
    }
}

void display(List L, VHeap V) {
    while (L != -1) {
        printf("%d -> ", V.H[L].elem);
        L = V.H[L].next;
    }
    printf("NULL\n");
}

int main() {
    VHeap V; List L = -1;
    initialize(&V);
    insertFirst(&L, &V, 10);
    insertFirst(&L, &V, 20);
    insertLast(&L, &V, 30);
    insertLast(&L, &V, 40);
    display(L, V);
    deleteElem(&L, &V, 30);
    display(L, V);
    deleteElem(&L, &V, 99);
}