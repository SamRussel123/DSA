#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int field:8;
} Set;

void initialize(Set *set) {
    set->field = 0;
}

void insert(Set *set, int element) {
    if (element >= 0 && element < 8) {
        set->field |= (1 << element);
    }
}

void delete(Set *set, int element) {
    if (element >= 0 && element < 8) {
        set->field &= ~(1 << element);
    }
}

bool find(Set set, int element) {
    if (element >= 0 && element < 8) {
        return (set.field & (1 << element)) != 0;
    }
    return false;
}

Set unionSet(Set A, Set B) {
    Set C;
    C.field = A.field | B.field;
    return C;
}

Set intersection(Set A, Set B) {
    Set C;
    C.field = A.field & B.field;
    return C;
}

Set difference(Set A, Set B) {
    Set C;
    C.field = A.field & ~(B.field);
    return C;
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
    Set A, B, C;
    initialize(&A);
    initialize(&B);

    insert(&A, 0);
    insert(&A, 4);
    insert(&A, 5);

    insert(&B, 2);
    insert(&B, 5);

    printf("A = "); display(A.field);
    printf("B = "); display(B.field);

    C = unionSet(A, B);
    printf("A ∪ B = "); display(C.field);

    C = intersection(A, B);
    printf("A ∩ B = "); display(C.field);

    C = difference(A, B);
    printf("A - B = "); display(C.field);

    delete(&A, 5);
    printf("A after delete 5 = "); display(A.field);

    printf("find 4 in A: %s\n", find(A,4) ? "true" : "false");
    printf("find 5 in A: %s\n", find(A,5) ? "true" : "false");

    return 0;
}