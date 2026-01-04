#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct node {
    int data;
    struct node *next;
} Node, *NodePtr;

typedef NodePtr Dict[MAX];

int hash(int x) { return (x % MAX + MAX) % MAX; }

void init(Dict D) {
    for (int i = 0; i < MAX; i++) D[i] = NULL;
}

bool inDict(Dict D, int x) {
    int i = hash(x);
    for (NodePtr p = D[i]; p; p = p->next) if (p->data == x) return true;
    return false;
}

void insert(Dict D, int x) {
    int i = hash(x);
    NodePtr *trav = &D[i];
    while (*trav && (*trav)->data != x) trav = &(*trav)->next;
    if (*trav == NULL) {
        NodePtr n = (NodePtr)malloc(sizeof(Node));
        if (!n) return;
        n->data = x;
        n->next = NULL;
        *trav = n;
    }
}

void deleteKey(Dict D, int x) {
    int i = hash(x);
    NodePtr *trav = &D[i];
    while (*trav && (*trav)->data != x) trav = &(*trav)->next;
    if (*trav) {
        NodePtr tmp = *trav;
        *trav = tmp->next;
        free(tmp);
    }
}

void print(Dict D) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: ", i);
        for (NodePtr p = D[i]; p; p = p->next) printf("%d ", p->data);
        printf("\n");
    }
}

int main() {
    Dict D; init(D);
    int a[] = {4, 2, 5, 2, 1, 12, 22};
    int n = sizeof(a)/sizeof(a[0]);

    for (int i = 0; i < n; i++) insert(D, a[i]);
    deleteKey(D, 5);
    print(D);
    return 0;
}