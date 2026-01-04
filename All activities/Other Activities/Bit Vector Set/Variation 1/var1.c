#include <stdio.h>
#include <stdbool.h>

void initialize(unsigned char *set) {
    *set = 0;
}

void insert(unsigned char *set, int element) {
    if (element >= 0 && element < 8) {
        *set |= (1 << element);
    }
}

void delete(unsigned char *set, int element) {
    if (element >= 0 && element < 8) {
        *set &= ~(1 << element);
    }
}

bool find(unsigned char set, int element) {
    if (element >= 0 && element < 8) {
        return (set & (1 << element)) != 0;
    }
    return false;
}

unsigned char union_set(unsigned char A, unsigned char B) {
    return A | B;
}

unsigned char intersection_set(unsigned char A, unsigned char B) {
    return A & B;
}

unsigned char difference_set(unsigned char A, unsigned char B) {
    return A & (~B);
}

void display(unsigned char set) {
    printf("{");
    int first = 1;
    for (int i = 0; i < 8; i++) {
        if (set & (1 << i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf("}\n");
}

int main() {
    unsigned char A, B, C;
    initialize(&A);
    initialize(&B);
    insert(&A, 1);
    insert(&A, 6);
    printf("A = "); display(A);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);
    printf("B = "); display(B);
    C = union_set(A, B);
    printf("A ∪ B = "); display(C);
    C = intersection_set(A, B);
    printf("A ∩ B = "); display(C);
    C = difference_set(A, B);
    printf("A - B = "); display(C);
    printf("Find 6 in A: %s\n", find(A, 6) ? "present" : "absent");
    printf("Find 3 in A: %s\n", find(A, 3) ? "present" : "absent");
    delete(&A, 6);
    printf("A after deleting 6 = "); display(A);
    return 0;
}