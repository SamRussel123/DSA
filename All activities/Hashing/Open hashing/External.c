#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define NIL (-1)

typedef struct {
    int value;
    int next;
} FNode;

int hash(int x) { return (x % MAX + MAX) % MAX; }

long heads_offset(void) { return 0; }
long nodes_offset(void) { return sizeof(int) * MAX; }

void init_file(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    int neg = NIL;
    for (int i = 0; i < MAX; i++) fwrite(&neg, sizeof(int), 1, fp);
    fflush(fp);
}

int read_head(FILE *fp, int idx) {
    int h;
    fseek(fp, heads_offset() + sizeof(int) * idx, SEEK_SET);
    fread(&h, sizeof(int), 1, fp);
    return h;
}

void write_head(FILE *fp, int idx, int h) {
    fseek(fp, heads_offset() + sizeof(int) * idx, SEEK_SET);
    fwrite(&h, sizeof(int), 1, fp);
    fflush(fp);
}

int append_node(FILE *fp, FNode node) {
    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    int index = (int)((end - nodes_offset()) / (long)sizeof(FNode));
    fwrite(&node, sizeof(FNode), 1, fp);
    fflush(fp);
    return index;
}

FNode read_node(FILE *fp, int idx) {
    FNode n;
    fseek(fp, nodes_offset() + (long)idx * sizeof(FNode), SEEK_SET);
    fread(&n, sizeof(FNode), 1, fp);
    return n;
}

void write_node(FILE *fp, int idx, FNode n) {
    fseek(fp, nodes_offset() + (long)idx * sizeof(FNode), SEEK_SET);
    fwrite(&n, sizeof(FNode), 1, fp);
    fflush(fp);
}

bool contains(FILE *fp, int x) {
    int b = hash(x);
    int cur = read_head(fp, b);
    while (cur != NIL) {
        FNode n = read_node(fp, cur);
        if (n.value == x) return true;
        cur = n.next;
    }
    return false;
}

void insert(FILE *fp, int x) {
    if (contains(fp, x)) return;

    int b = hash(x);
    int head = read_head(fp, b);

    FNode newn;
    newn.value = x;
    newn.next = head;

    int newIndex = append_node(fp, newn);
    write_head(fp, b, newIndex);
}

void print_table(FILE *fp) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: ", i);
        int cur = read_head(fp, i);
        while (cur != NIL) {
            FNode n = read_node(fp, cur);
            printf("%d ", n.value);
            cur = n.next;
        }
        printf("\n");
    }
}

int main() {
    FILE *fp = fopen("open_external.bin", "w+b");
    if (!fp) return 1;

    init_file(fp);

    int a[] = {4, 2, 5, 2, 1, 12, 22, 32, 42};
    int n = sizeof(a)/sizeof(a[0]);

    for (int i = 0; i < n; i++) insert(fp, a[i]);

    print_table(fp);

    fclose(fp);
    return 0;
}