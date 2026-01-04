#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define EMPTY (-1)
#define DELETED (-2)

int hash(int x) { return (x % MAX + MAX) % MAX; }

void init_file(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    int v = EMPTY;
    for (int i = 0; i < MAX; i++) fwrite(&v, sizeof(int), 1, fp);
    fflush(fp);
}

int read_slot(FILE *fp, int idx) {
    int v;
    fseek(fp, (long)idx * sizeof(int), SEEK_SET);
    fread(&v, sizeof(int), 1, fp);
    return v;
}

void write_slot(FILE *fp, int idx, int v) {
    fseek(fp, (long)idx * sizeof(int), SEEK_SET);
    fwrite(&v, sizeof(int), 1, fp);
    fflush(fp);
}

bool contains(FILE *fp, int x) {
    int start = hash(x);
    for (int k = 0; k < MAX; k++) {
        int idx = (start + k) % MAX;
        int v = read_slot(fp, idx);
        if (v == EMPTY) return false;
        if (v == x) return true;
    }
    return false;
}

bool insert(FILE *fp, int x) {
    if (contains(fp, x)) return false;
    int start = hash(x);

    for (int k = 0; k < MAX; k++) {
        int idx = (start + k) % MAX;
        int v = read_slot(fp, idx);
        if (v == EMPTY || v == DELETED) {
            write_slot(fp, idx, x);
            return true;
        }
    }
    return false;
}

bool deleteKey(FILE *fp, int x) {
    int start = hash(x);
    for (int k = 0; k < MAX; k++) {
        int idx = (start + k) % MAX;
        int v = read_slot(fp, idx);
        if (v == EMPTY) return false;
        if (v == x) {
            write_slot(fp, idx, DELETED);
            return true;
        }
    }
    return false;
}

void print_table(FILE *fp) {
    for (int i = 0; i < MAX; i++) {
        int v = read_slot(fp, i);
        if (v == EMPTY) printf("[%d]: EMPTY\n", i);
        else if (v == DELETED) printf("[%d]: DELETED\n", i);
        else printf("[%d]: %d\n", i, v);
    }
}

int main() {
    FILE *fp = fopen("closed_external.bin", "w+b");
    if (!fp) return 1;

    init_file(fp);

    int a[] = {4, 2, 5, 2, 1, 12, 22};
    int n = sizeof(a)/sizeof(a[0]);

    for (int i = 0; i < n; i++) insert(fp, a[i]);
    deleteKey(fp, 5);
    print_table(fp);

    fclose(fp);
    return 0;
}