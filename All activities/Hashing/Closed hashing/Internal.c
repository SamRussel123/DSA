#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define EMPTY (-1)
#define DELETED (-2)

int hash(int x) { return (x % MAX + MAX) % MAX; }

void init(int T[]) {
    for (int i = 0; i < MAX; i++) T[i] = EMPTY;
}

bool contains(int T[], int x) {
    int i = hash(x);
    for (int k = 0; k < MAX; k++) {
        int idx = (i + k) % MAX;
        if (T[idx] == EMPTY) return false;
        if (T[idx] == x) return true;
    }
    return false;
}

bool insert(int T[], int x) {
    if (contains(T, x)) return false;
    int i = hash(x);

    for (int k = 0; k < MAX; k++) {
        int idx = (i + k) % MAX;
        if (T[idx] == EMPTY || T[idx] == DELETED) {
            T[idx] = x;
            return true;
        }
    }
    return false;
}

bool deleteKey(int T[], int x) {
    int i = hash(x);
    for (int k = 0; k < MAX; k++) {
        int idx = (i + k) % MAX;
        if (T[idx] == EMPTY) return false;
        if (T[idx] == x) {
            T[idx] = DELETED;
            return true;
        }
    }
    return false;
}

void print(int T[]) {
    for (int i = 0; i < MAX; i++) {
        if (T[i] == EMPTY) printf("[%d]: EMPTY\n", i);
        else if (T[i] == DELETED) printf("[%d]: DELETED\n", i);
        else printf("[%d]: %d\n", i, T[i]);
    }
}

int main() {
    int T[MAX];
    init(T);

    int a[] = {4, 2, 5, 2, 1, 12, 22};
    int n = sizeof(a)/sizeof(a[0]);

    for (int i = 0; i < n; i++) insert(T, a[i]);
    deleteKey(T, 5);
    print(T);
    return 0;
}